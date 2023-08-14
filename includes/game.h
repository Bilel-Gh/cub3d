/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 03:11:16 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 15:27:09 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cub3d.h"

# define MOVE_SPEED 0.5
# define RADIAN 0.5
# define PLAYER_SIZE 0.2

enum			e_key
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	ESC = 65307,
	LEFT = 65361,
	RIGHT = 65363,
};

typedef struct s_game_infos
{
	float		camera_x;
	float		ray_dir_x;
	float		ray_dir_y;
	int			map_x;
	int			map_y;
	float		side_dist_x;
	float		side_dist_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
	t_texture	*texture;
	int			tex_x;
	float		wall_x;
	float		step;
}				t_game_infos;

typedef struct s_direction
{
	int			left;
	int			right;
	int			top;
	int			bottom;
}				t_direction;

int				ft_init_and_start_game(t_data *data);

// raycasting
void			ft_set_direction_ray(t_data *data, t_game_infos *game_infos);
void			ft_get_distance_to_wall(t_data *data, t_game_infos *game_infos);
void			ft_get_good_texture(t_data *data, t_game_infos *game_infos);
void			ft_get_good_pixel(t_data *data, t_game_infos *game_infos);
void			ft_draw_textured_line(t_data *data, int x,
					t_game_infos *game_infos);

// movement
void			ft_move_player(t_data *data, int keycode);
int				ft_is_movement_key(int keycode);
void			ft_rotate_cam_left(t_data *data);
void			ft_rotate_cam_right(t_data *data);

// game utils
int				ft_close_window(t_data *data);
int				ft_put_pixel_to_image(t_data *data, int x, int y, int color);
void			draw_background(t_data *data);

#endif
