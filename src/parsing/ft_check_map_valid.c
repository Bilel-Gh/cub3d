/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_valid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:09:16 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 15:03:18 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// recupere les coordonnees de la position du joueur et sa direction
// je stock dans data->player la position avec +0.5
// pour etre au centre de la case et pas dans le coin
// je stock dans data->player->dir la direction du joueur
// en fonction de la lettre de la map
// la structure t_vector représente une direction dans un plan 2D
// exemple : si la lettre est 'N' alors la direction est (0, -1)
// car le joueur regarde vers l'axe negatif des y' x = 0 et y = -1'
void	ft_get_spawn_info(t_data *data, int **map_ints)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map_height)
	{
		j = -1;
		while (++j < data->map_width)
		{
			if (map_ints[i][j] == SPAWN)
			{
				data->player->pos.x = (float)j + 0.5;
				data->player->pos.y = (float)i + 0.5;
				if (data->map[i][j] == 'N')
					ft_set_vector(&data->player->dir, 0, -1);
				else if (data->map[i][j] == 'S')
					ft_set_vector(&data->player->dir, 0, 1);
				else if (data->map[i][j] == 'E')
					ft_set_vector(&data->player->dir, 1, 0);
				else if (data->map[i][j] == 'W')
					ft_set_vector(&data->player->dir, -1, 0);
			}
		}
	}
}

// fonction qui verifie la prochaine case ou on veut aller et valide
// verifie si les coordonnées (x, y) sont en dehors des limites de la carte.
// et si la case à la position (x, y) a deja ete visite ou est un mur.
static int	is_valid(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->x_max || y < 0 || y >= map->y_max)
		return (0);
	if (map->valide_case[y][x] == true || map->map[y][x] == WALL)
		return (0);
	return (1);
}

// fonction qui part d'un point de la map
// et cherche toute les cases qui sont accessibles depuis ce point
// et les marque comme valide dans la le double tableau map->valide_case
static void	dfs(t_map *map, int x, int y)
{
	const int	x_move[] = {0, 1, 0, -1};
	const int	y_move[] = {-1, 0, 1, 0};
	int			next_case_x;
	int			next_case_y;
	int			i;

	i = 0;
	map->valide_case[y][x] = true;
	while (i < 4)
	{
		next_case_x = x + x_move[i];
		next_case_y = y + y_move[i];
		if (is_valid(map, next_case_x, next_case_y))
			dfs(map, next_case_x, next_case_y);
		i++;
	}
}

// fonction qui cree cree une copie de la map
// a partir de de sa taille (map_width, map_height)
// et qui initialise chaque case a 0
static int	**map_size_dup(int map_width, int map_height)
{
	int	**map_dup;
	int	i;

	map_dup = ft_calloc(map_height, sizeof(int *));
	if (!map_dup)
		return (NULL);
	i = 0;
	while (i < map_height)
	{
		map_dup[i] = ft_calloc(map_width, sizeof(int));
		if (!map_dup[i])
			return (ft_free_tabs(map_dup, i), NULL);
		i++;
	}
	return (map_dup);
}

// fonction qui verifie si la map est valide grace a la fonction dfs
int	ft_check_map_valid(t_data *data, int **map_ints)
{
	t_map		map;
	t_player	*player;
	int			x;
	int			y;

	player = data->player;
	map.map = map_ints;
	map.x_max = data->map_width;
	map.y_max = data->map_height;
	if (player->pos.x == 0 || player->pos.x == map.x_max - 1 || \
		player->pos.y == 0 || player->pos.y == map.y_max - 1)
		return (ft_error("Error\nSpawn pas au bon endroit\n"), EXIT_FAILURE);
	map.valide_case = map_size_dup(map.x_max, map.y_max);
	if (!map.valide_case)
		return (ft_error(ERROR_MALLOC));
	x = player->pos.x;
	y = player->pos.y;
	dfs(&map, x, y);
	if (ft_check_map_border(&map))
		return (ft_free_tabs(map.valide_case, map.y_max), EXIT_FAILURE);
	return (ft_free_tabs(map.valide_case, map.y_max), EXIT_SUCCESS);
}
