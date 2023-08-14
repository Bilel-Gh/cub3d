/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:07:44 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 14:22:32 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_data(t_data *data, char *file_name)
{
	int	i;

	printf("\nFILE NAME : ./%s\n", file_name);
	printf("\nNO : %s\n", data->north->path);
	printf("SO : %s\n", data->south->path);
	printf("WE : %s\n", data->west->path);
	printf("EA : %s\n", data->east->path);
	printf("\nFLOOR : %d rgb(%d, %d, %d)\n", data->floor_color,
		data->floor_color >> 16 & 0xFF, data->floor_color >> 8 & 0xFF,
		data->floor_color & 0xFF);
	printf("CEILING : %d rgb(%d, %d, %d)\n", data->ceiling_color,
		data->ceiling_color >> 16 & 0xFF, data->ceiling_color >> 8 & 0xFF,
		data->ceiling_color & 0xFF);
	printf("\nMAP :\n");
	i = 0;
	while (data->map[i])
		printf("%s\n", data->map[i++]);
	printf("\nMAP HEIGHT : %d, MAP WIDTH : %d\n", data->map_height,
		data->map_width);
	printf("\nPLAYER POSITION : x = %f, y = %f\n", data->player->pos.x,
		data->player->pos.y);
	printf("PLAYER DIRECTION : x = %f, y = %f\n\n", data->player->dir.x,
		data->player->dir.y);
}

// fonction qui free la structure t_parsing
// si les textures sont dans la structure t_data on ne free pas les textures
// car elles seront free dans la structure t_data apres le return dans le main
void	free_parsing_s(t_parsing *parsing, bool is_texture_in_data)
{
	int	i;

	if (parsing->file_content)
		ft_free((void **)&(parsing->file_content));
	if (parsing->file_content_split)
		ft_free_strs(parsing->file_content_split);
	if (parsing->texture_path)
	{
		if (is_texture_in_data)
		{
			i = 0;
			while (i < 4)
			{
				ft_free((void **)&(parsing->texture_path[i]));
				i++;
			}
		}
		free(parsing->texture_path);
	}
	ft_bzero(parsing, sizeof(t_parsing));
}

// fonction qui met tout le contenu du fichier dans parsing->file_content
int	ft_read_file(char **file_content, int *fd)
{
	char	*line;
	char	*tmp;

	line = get_next_line(*fd);
	while (line)
	{
		if (*file_content != NULL)
		{
			tmp = *file_content;
			*file_content = ft_strjoin(*file_content, line);
			if (!file_content)
				return (free(tmp), free(line), ft_error(ERROR_MALLOC));
			ft_free((void **)&tmp);
			free(line);
		}
		else
			*file_content = line;
		line = get_next_line(*fd);
	}
	ft_close(fd);
	return (EXIT_SUCCESS);
}

// set a \0 le 1er car de chaque ligne du fichier qui n'est pas la map
// exemple : NO ./textures/north.xpm -> \0O ./textures/north.xpm
// permet d'ignorer les infos dans la map dans les prochaines fonctions
int	ft_remove_infos_from_file_content(char ***file_content)
{
	int	i;

	i = 0;
	while ((*file_content)[i])
	{
		if (ft_strncmp((*file_content)[i], "NO", 2) == 0)
			(*file_content)[i][0] = '\0';
		else if (ft_strncmp((*file_content)[i], "SO", 2) == 0)
			(*file_content)[i][0] = '\0';
		else if (ft_strncmp((*file_content)[i], "WE", 2) == 0)
			(*file_content)[i][0] = '\0';
		else if (ft_strncmp((*file_content)[i], "EA", 2) == 0)
			(*file_content)[i][0] = '\0';
		else if (ft_strncmp((*file_content)[i], "F", 1) == 0)
			(*file_content)[i][0] = '\0';
		else if (ft_strncmp((*file_content)[i], "C", 1) == 0)
			(*file_content)[i][0] = '\0';
		i++;
	}
	return (EXIT_SUCCESS);
}

// fonction qui check si le fichier est valide
int	ft_parsing(t_data *data, char *file_name)
{
	t_parsing	parsing;

	(void)data;
	ft_bzero(&parsing, sizeof(t_parsing));
	parsing.fd = -1;
	if (ft_check_and_read_file(&file_name, &parsing))
		return (EXIT_FAILURE);
	if (ft_get_file_content_split(&parsing))
		return (EXIT_FAILURE);
	if (ft_do_check_file_infos(data, &parsing))
		return (EXIT_FAILURE);
	if (ft_do_remove_info_from_file(&parsing))
		return (EXIT_FAILURE);
	if (ft_do_create_and_init_map(data, &parsing))
		return (EXIT_FAILURE);
	if (ft_check_texture_path(data, &parsing))
	{
		free_parsing_s(&parsing, true);
		return (EXIT_FAILURE);
	}
	print_data(data, file_name);
	return (free_parsing_s(&parsing, true), EXIT_SUCCESS);
}
