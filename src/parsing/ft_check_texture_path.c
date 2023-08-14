/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_texture_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:09:08 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 15:00:27 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_direction(t_data *data, char **file_content, int dir)
{
	if (dir == NORTH)
	{
		if (ft_get_texture_info(data->north, file_content) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (dir == SOUTH)
	{
		if (ft_get_texture_info(data->south, file_content) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (dir == EAST)
	{
		if (ft_get_texture_info(data->east, file_content) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (dir == WEST)
	{
		if (ft_get_texture_info(data->west, file_content) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// fonction qui va chercher les path des textures
// dans la structure parsing et les met dans la structure data
void	get_path_texture_in_data(t_data *data, t_parsing *parsing)
{
	data->north->path = parsing->texture_path[NO];
	data->south->path = parsing->texture_path[SO];
	data->east->path = parsing->texture_path[EA];
	data->west->path = parsing->texture_path[WE];
}

int	ft_check_texture_path(t_data *data, t_parsing *parsing)
{
	int		i;
	int		fd;
	char	*file_content;
	char	**file_content_split;

	get_path_texture_in_data(data, parsing);
	i = -1;
	fd = -1;
	file_content = NULL;
	while (++i < 4)
	{
		if (ft_check_file(parsing->texture_path[i], &fd, XPM) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_read_file(&file_content, &fd) == EXIT_FAILURE)
			return (free(file_content), EXIT_FAILURE);
		ft_close(&fd);
		file_content_split = ft_split(file_content, '\n');
		if (!file_content_split)
			return (free(file_content), ft_error(ERROR_MALLOC));
		ft_free((void **)&file_content);
		if (get_direction(data, file_content_split, i) == EXIT_FAILURE)
			return (ft_free_strs(file_content_split), EXIT_FAILURE);
		ft_free_strs(file_content_split);
	}
	return (EXIT_SUCCESS);
}
