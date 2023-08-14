/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:38:56 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/11 17:47:25 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_close_window(t_data *data)
{
	if (data->win_infos.img)
		mlx_destroy_image(data->win_infos.mlx, data->win_infos.img);
	if (data->win_infos.win)
		mlx_destroy_window(data->win_infos.mlx, data->win_infos.win);
	if (data->win_infos.mlx)
		mlx_destroy_display(data->win_infos.mlx);
	ft_free_data_s(data);
	exit(EXIT_SUCCESS);
}

int	ft_put_pixel_to_image(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->win_infos.img_data + (y * data->win_infos.size_line + x
			* (data->win_infos.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (EXIT_SUCCESS);
}

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (y < WIN_HEIGHT / 2)
				ft_put_pixel_to_image(data, x, y, data->ceiling_color);
			else
				ft_put_pixel_to_image(data, x, y, data->floor_color);
			y++;
		}
		x++;
	}
}
