/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_start_game.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:36:38 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/11 18:01:48 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// fonction qui initialise les infos du jeu
// camera_x est la coordonnee x du plan de la camera (- 1g ou 0m ou 1d)
// ray_dir_x et y sont les coordonnees x et y du vecteur de direction du rayon
// map_x et y representent le carre dans lequel se trouve le rayon
// delta_dist_x est la distance que le rayon doit parcourir
// pr toucher une ligne verticale(x)
// delta_dist_y est la distance que le rayon doit parcourir
// pr toucher une ligne horizontale(y)
// hit est un booleen qui indique si le rayon a touche un mur
void	ft_init_game_infos(t_data *data, t_game_infos *game_infos, int x)
{
	game_infos->camera_x = 2 * x / (float)WIN_WIDTH - 1;
	game_infos->ray_dir_x = data->player->dir.x + data->player->plan.x
		* game_infos->camera_x;
	game_infos->ray_dir_y = data->player->dir.y + data->player->plan.y
		* game_infos->camera_x;
	game_infos->map_x = (int)data->player->pos.x;
	game_infos->map_y = (int)data->player->pos.y;
	game_infos->delta_dist_x = fabs(1 / game_infos->ray_dir_x);
	game_infos->delta_dist_y = fabs(1 / game_infos->ray_dir_y);
	game_infos->hit = 0;
}

int	ft_start_game(t_data *data)
{
	int				x;
	t_game_infos	game_infos;

	x = 0;
	draw_background(data);
	while (x < WIN_WIDTH)
	{
		ft_init_game_infos(data, &game_infos, x);
		ft_set_direction_ray(data, &game_infos);
		ft_get_distance_to_wall(data, &game_infos);
		ft_get_good_texture(data, &game_infos);
		ft_get_good_pixel(data, &game_infos);
		ft_draw_textured_line(data, x, &game_infos);
		x++;
	}
	mlx_put_image_to_window(data->win_infos.mlx, data->win_infos.win,
		data->win_infos.img, 0, 0);
	return (EXIT_SUCCESS);
}

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		ft_close_window(data);
	else if (ft_is_movement_key(keycode))
	{
		printf("keycode = %d\n", keycode);
		ft_move_player(data, keycode);
	}
	else if (keycode == LEFT)
	{
		printf("keycode = %d\n", keycode);
		ft_rotate_cam_left(data);
	}
	else if (keycode == RIGHT)
	{
		printf("keycode = %d\n", keycode);
		ft_rotate_cam_right(data);
	}
	ft_start_game(data);
	mlx_put_image_to_window(data->win_infos.mlx, data->win_infos.win,
		data->win_infos.img, 0, 0);
	return (EXIT_SUCCESS);
}

void	ft_start(t_data *data)
{
	mlx_hook(data->win_infos.win, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->win_infos.win, 17, 0L, ft_close_window, data);
	mlx_do_key_autorepeaton(data->win_infos.mlx);
	draw_background(data);
	ft_start_game(data);
	mlx_put_image_to_window(data->win_infos.mlx, data->win_infos.win,
		data->win_infos.img, 0, 0);
	mlx_loop(data->win_infos.mlx);
}

int	ft_init_and_start_game(t_data *data)
{
	data->player->plan.x = data->player->dir.y * -1;
	data->player->plan.y = data->player->dir.x;
	data->win_infos.mlx = mlx_init();
	if (!data->win_infos.mlx)
		return (EXIT_FAILURE);
	data->win_infos.win = mlx_new_window(data->win_infos.mlx, WIN_WIDTH,
			WIN_HEIGHT, "cub3d");
	if (!data->win_infos.win)
		return (ft_close_window(data));
	data->win_infos.img = mlx_new_image(data->win_infos.mlx, WIN_WIDTH,
			WIN_HEIGHT);
	if (!data->win_infos.img)
		return (ft_close_window(data));
	data->win_infos.img_data = mlx_get_data_addr(data->win_infos.img,
			&data->win_infos.bits_per_pixel,
			&data->win_infos.size_line,
			&data->win_infos.endian);
	if (!data->win_infos.img_data)
		return (ft_close_window(data));
	ft_start(data);
	return (EXIT_SUCCESS);
}
