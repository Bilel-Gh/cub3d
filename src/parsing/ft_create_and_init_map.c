/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_and_init_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:09:04 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 14:48:36 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

// fonction qui recupre la map sans les infos et la stock dans data->map
int	create_map(t_data *data, char **file_content)
{
	int		nb_line;
	char	**map;
	int		i;
	int		j;

	i = 0;
	nb_line = ft_count_nb_line(file_content);
	while (file_content[i] && file_content[i][0] == '\0')
		i++;
	if (i < 6)
		return (ft_error("Error\n Fichier de map invalide\n"));
	map = (char **)ft_calloc(nb_line - i + 1, sizeof(char *));
	if (!map)
		return (ft_error(ERROR_MALLOC));
	j = 0;
	while (file_content[i])
	{
		map[j] = ft_strdup(file_content[i]);
		if (!map[j])
			return (ft_free_strs_n(map, j), ft_error(ERROR_MALLOC));
		j++;
		i++;
	}
	data->map = map;
	return (EXIT_SUCCESS);
}

// fonction qui verifie qu'il y a bien une position de depart du joueur
// et qu'il n'y en a pas plusieurs
int	ft_check_map_spawn(char **map)
{
	char	*spawn_char;
	int		spawn;
	int		i;
	int		j;

	spawn_char = "NEWS";
	spawn = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(spawn_char, map[i][j]))
				spawn++;
			j++;
		}
		i++;
	}
	if (spawn != 1)
		return (ft_error("Error\n Pas de spawn ou plusieurs spawn\n"));
	return (EXIT_SUCCESS);
}

//  fonction qui va calculer la largeur et la hauteur de la map char **
//  et qui va allouer la memoire pour le tableau d'entier
// qui va contenir la map et set toutes les valeurs allouer a 0
int	ft_create_map_ints(t_data *data, int ***map_ints)
{
	int	i;

	data->map_width = 0;
	i = 0;
	while (data->map[i])
	{
		if ((int)ft_strlen(data->map[i]) > data->map_width)
			data->map_width = ft_strlen(data->map[i]);
		i++;
	}
	data->map_height = i;
	(*map_ints) = ft_calloc(data->map_height, sizeof(int *));
	if (!(*map_ints))
		return (ft_error(ERROR_MALLOC));
	i = 0;
	while (i < data->map_height)
	{
		(*map_ints)[i] = ft_calloc(data->map_width, sizeof(int));
		if (!(*map_ints)[i])
			return (ft_free_tabs((*map_ints), i),
				ft_error(ERROR_MALLOC));
		i++;
	}
	return (EXIT_SUCCESS);
}

// va remplir le tableau d'entier avec les valeurs correspondantes
// 0 = espace vide | 1 = mur | 2 = espace | 3 = spawn
int	ft_init_map_ints(t_data *data, int **map_ints)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == ' ')
				map_ints[y][x] = EMPTY;
			else if (data->map[y][x] == '1')
				map_ints[y][x] = WALL;
			else if (data->map[y][x] == '0')
				map_ints[y][x] = SPACE;
			else if (data->map[y][x] == 'N'
						|| data->map[y][x] == 'S'
						|| data->map[y][x] == 'E'
						|| data->map[y][x] == 'W')
				map_ints[y][x] = SPAWN;
			else
				return (ft_error("Error\n charactere invalide dans la map\n"));
		}
	}
	return (EXIT_SUCCESS);
}

// transforme la map presentée sous forme de char ** en int **
// et vérifie que la map est valide
int	ft_create_and_init_map(t_data *data, char **file_content)
{
	int	**map_ints;

	map_ints = NULL;
	if (create_map(data, file_content))
		return (EXIT_FAILURE);
	if (data->map[0] == NULL)
		return (ft_error("Error\n pas de map dans le fichier\n"));
	if (is_invalid_map(data->map))
		return (ft_error("Error\nMap invalide\n"));
	if ((ft_strlen(data->map[0]) >= 1 && data->map[1] == NULL) || \
		(data->map[0] != NULL && data->map[1] != NULL && data->map[2] == NULL))
		return (ft_error("Error\nMap trop petite\n"));
	if (ft_check_map_spawn(data->map))
		return (EXIT_FAILURE);
	if (ft_create_map_ints(data, &map_ints))
		return (EXIT_FAILURE);
	if (ft_init_map_ints(data, map_ints))
		return (ft_free_tabs(map_ints, data->map_height), EXIT_FAILURE);
	ft_get_spawn_info(data, map_ints);
	if (ft_check_map_valid(data, map_ints))
		return (ft_free_tabs(map_ints, data->map_height), EXIT_FAILURE);
	return (ft_free_tabs(map_ints, data->map_height), EXIT_SUCCESS);
}
