/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_infos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:09:28 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 15:26:17 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//fonction qui si le format de couleur est bon [0-255],[0-255],[0-255]
int	ft_check_line_color(char *line)
{
	int	digit;
	int	i;

	i = 1;
	digit = 0;
	while (line[i])
	{
		if (ft_isalpha(line[i]))
			return (ft_error("Error\n mauvais format pour la couleur\n"));
		while (line[i] && (line[i] == ' ' || ft_isdigit(line[i])))
			i++;
		if (line[i] == 0)
		{
			digit++;
			break ;
		}
		if (line[i] == ',' && i++)
			digit++;
		else
			return (ft_error("Error\n mauvais format pour la couleur\n"));
	}
	if (digit != 3)
		return (ft_error("Error\n mauvais format pour la couleur\n"));
	return (EXIT_SUCCESS);
}

// recupere les composantes rgb de la couleur et les stock dans un tableau
// puis verifie si les valeurs sont comprises entre 0 et 255
// si c'est le cas on stock la couleur dans la variable color
// avec une conversion en hexadecimal pour avoir la couleur finale
int	ft_get_color(int *color, char *line, int *is_info)
{
	int	i;
	int	color_rgb[3];

	i = 1;
	if (ft_check_line_color(line))
		return (EXIT_FAILURE);
	color_rgb[0] = ft_atoi(&line[i]);
	while (line[i] && line[i] != ',')
		i++;
	color_rgb[1] = ft_atoi(&line[++i]);
	while (line[i] && line[i] != ',')
		i++;
	color_rgb[2] = ft_atoi(&line[++i]);
	i = 0;
	while (i < 3)
	{
		if (color_rgb[i] < 0 || color_rgb[i] > 255)
			return (ft_error("Error\n mauvaise valeur de couleur\n"));
		i++;
	}
	*color = color_rgb[0] << 16 | color_rgb[1] << 8 | color_rgb[2];
	*is_info = true;
	return (EXIT_SUCCESS);
}

// recupere le chemin de la texture et le stock dans la variable texture_path
// qui correspond a l'index de la texture de la direction voulu
//  dans le tableau parsing->texture_path
int	ft_get_texture(char **texture_path, char *line, int *is_info)
{
	int	start;

	if (*is_info == true)
		return (ft_error("Error\n plusieurs textures pour la même direction\n"));
	start = 2;
	while (line[start] == ' ')
		start++;
	*texture_path = ft_substr(line, start, ft_strlen(line));
	if (!*texture_path)
		return (ft_error(ERROR_MALLOC));
	*is_info = true;
	return (EXIT_SUCCESS);
}

// verifie si les informations de la map sont bien presentes et son correctes
// si oui stock les chemins des textures dans le tableau parsing->texture_path
// chaque case du tableau correspond a une direction [0:NO, 1:SO, 2:WE, 3:EA]
// on stock aussi les couleur du sol et du plafond
// dans les variables data->floor_color et data->ceiling_color
int	ft_check_file_infos_and_fill(t_data *data, char **texture_path, char **file,
		int is_info[6])
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (file[i])
	{
		if (ft_strncmp(file[i], "NO ", 3) == 0)
			status = ft_get_texture(&texture_path[NO], file[i], &is_info[NO]);
		else if (ft_strncmp(file[i], "SO ", 3) == 0)
			status = ft_get_texture(&texture_path[SO], file[i], &is_info[SO]);
		else if (ft_strncmp(file[i], "WE ", 3) == 0)
			status = ft_get_texture(&texture_path[WE], file[i], &is_info[WE]);
		else if (ft_strncmp(file[i], "EA ", 3) == 0)
			status = ft_get_texture(&texture_path[EA], file[i], &is_info[EA]);
		else if (ft_strncmp(file[i], "F ", 2) == 0)
			status = ft_get_color(&data->floor_color, file[i], &is_info[F]);
		else if (ft_strncmp(file[i], "C ", 2) == 0)
			status = ft_get_color(&data->ceiling_color, file[i], &is_info[C]);
		if (status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_check_file_infos(t_data *data, t_parsing *parsing)
{
	int	is_info[6];
	int	i;
	int	nb_infos_recup;

	i = 0;
	parsing->texture_path = ft_calloc(4, sizeof(char *));
	if (!parsing->texture_path)
		return (ft_error(ERROR_MALLOC));
	while (i < 6)
		is_info[i++] = false;
	if (ft_check_file_infos_and_fill(data, parsing->texture_path,
			parsing->file_content_split, is_info))
		return (EXIT_FAILURE);
	nb_infos_recup = ft_get_nb_infos_recup(is_info);
	if (nb_infos_recup != 6)
		return (ft_error("Error\ninfos manquantes\n"));
	i = 0;
	while (i < 4)
		if (ft_strcmp(parsing->texture_path[i++], "") == 0)
			return (ft_error("Error\n infos manquantes\n"));
	return (EXIT_SUCCESS);
}
