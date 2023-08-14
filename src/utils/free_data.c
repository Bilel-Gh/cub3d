/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:08:01 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 14:15:33 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// bonne pratique de set a NULL un pointeur apres free
// pour faciliter le debug et eviter les segfaults
void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

// free un tableau de string et set a NULL
void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		ft_free((void **)&strs[i]);
		i++;
	}
	free(strs);
}

// free un tableau de string et set a NULL en parcourant n elements
void	ft_free_strs_n(char **strs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_free((void **)&strs[i]);
		i++;
	}
	free(strs);
}

// free un tableau de int et set a NULL
void	ft_free_tabs(int **tabs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_free((void **)&tabs[i]);
		i++;
	}
	free(tabs);
}

// free la structure data
void	ft_free_data_s(t_data *data)
{
	if (data->north && data->north->path)
	{
		ft_free((void **)&(data->north->path));
		ft_free_tabs(data->north->data, data->north->height);
	}
	if (data->south && data->south->path)
	{
		ft_free((void **)&(data->south->path));
		ft_free_tabs(data->south->data, data->south->height);
	}
	if (data->east && data->east->path)
	{
		ft_free((void **)&(data->east->path));
		ft_free_tabs(data->east->data, data->east->height);
	}
	if (data->west && data->west->path)
	{
		ft_free((void **)&(data->west->path));
		ft_free_tabs(data->west->data, data->west->height);
	}
	if (data->map)
		ft_free_strs(data->map);
	if (data->win_infos.mlx)
		ft_free((void **)&(data->win_infos.mlx));
	ft_bzero(data, sizeof(t_data));
}
