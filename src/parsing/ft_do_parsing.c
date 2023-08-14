/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:27:05 by bghandri          #+#    #+#             */
/*   Updated: 2023/07/31 01:43:12 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_check_and_read_file(char **file_name, t_parsing *parsing)
{
	if (ft_check_file(*file_name, &(parsing->fd), CUB))
	{
		free_parsing_s(parsing, false);
		return (EXIT_FAILURE);
	}
	if (ft_read_file(&(parsing->file_content), &(parsing->fd)))
	{
		free_parsing_s(parsing, false);
		return (EXIT_FAILURE);
	}
	if (!&(parsing->file_content))
	{
		free_parsing_s(parsing, false);
		ft_error(ERROR_MALLOC);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_get_file_content_split(t_parsing *parsing)
{
	parsing->file_content_split = ft_split_newline(parsing->file_content);
	if (!parsing->file_content_split)
	{
		free_parsing_s(parsing, false);
		ft_error(ERROR_MALLOC);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_do_check_file_infos(t_data *data, t_parsing *parsing)
{
	if (ft_check_file_infos(data, parsing))
	{
		free_parsing_s(parsing, false);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_do_remove_info_from_file(t_parsing *parsing)
{
	if (ft_remove_infos_from_file_content(&(parsing->file_content_split)))
	{
		free_parsing_s(parsing, false);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_do_create_and_init_map(t_data *data, t_parsing *parsing)
{
	if (ft_create_and_init_map(data, parsing->file_content_split))
	{
		free_parsing_s(parsing, true);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
