/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:35:29 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/11 18:35:56 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// fonction qui set side_dist_x et side_dist_y et step_x et step_y
// side_dist(x)(y) est la distance que le rayon doit parcourir pr toucher
//		les premieres ligne (x) et (y)
// step_x et step_y representent le sens dans lequel le rayon doit se deplacer
void	ft_set_direction_ray(t_data *data, t_game_infos *game_infos)
{
	if (game_infos->ray_dir_x < 0)
	{
		game_infos->step_x = -1;
		game_infos->side_dist_x = (data->player->pos.x - game_infos->map_x)
			* game_infos->delta_dist_x;
	}
	else
	{
		game_infos->step_x = 1;
		game_infos->side_dist_x = (game_infos->map_x + 1.0
				- data->player->pos.x) * game_infos->delta_dist_x;
	}
	if (game_infos->ray_dir_y < 0)
	{
		game_infos->step_y = -1;
		game_infos->side_dist_y = (data->player->pos.y - game_infos->map_y)
			* game_infos->delta_dist_y;
	}
	else
	{
		game_infos->step_y = 1;
		game_infos->side_dist_y = (game_infos->map_y + 1.0
				- data->player->pos.y) * game_infos->delta_dist_y;
	}
}

// fonction qui calcule la distance entre le joueur et le mur
// on calcule en realite la distance le plan de la camera et le mur
// pour eviter les distorsions de perspective
// on utilise l'algorithme DDA (Digital Differential Analysis)
void	ft_get_distance_to_wall(t_data *data, t_game_infos *game_infos)
{
	while (game_infos->hit == 0)
	{
		if (game_infos->side_dist_x < game_infos->side_dist_y)
		{
			game_infos->side_dist_x += game_infos->delta_dist_x;
			game_infos->map_x += game_infos->step_x;
			game_infos->side = 0;
		}
		else
		{
			game_infos->side_dist_y += game_infos->delta_dist_y;
			game_infos->map_y += game_infos->step_y;
			game_infos->side = 1;
		}
		if (data->map[game_infos->map_y][game_infos->map_x] == '1')
			game_infos->hit = 1;
	}
	if (game_infos->side == 0)
		game_infos->perp_wall_dist = (game_infos->map_x - data->player->pos.x
				+ (1 - game_infos->step_x) / 2) / game_infos->ray_dir_x;
	else
		game_infos->perp_wall_dist = (game_infos->map_y - data->player->pos.y
				+ (1 - game_infos->step_y) / 2) / game_infos->ray_dir_y;
	game_infos->line_height = (int)(WIN_HEIGHT / game_infos->perp_wall_dist);
}

// fonction qui calcule la hauteur de la ligne de pixel a afficher
// et qui set la bonne texture a afficher en fonction du mur touche par le rayon
void	ft_get_good_texture(t_data *data, t_game_infos *game_infos)
{
	game_infos->draw_start = -game_infos->line_height / 2 + WIN_HEIGHT / 2;
	if (game_infos->draw_start < 0)
		game_infos->draw_start = 0;
	game_infos->draw_end = game_infos->line_height / 2 + WIN_HEIGHT / 2;
	if (game_infos->draw_end >= WIN_HEIGHT)
		game_infos->draw_end = WIN_HEIGHT - 1;
	game_infos->texture = NULL;
	if (game_infos->side == 0 && game_infos->ray_dir_x > 0)
		game_infos->texture = data->east;
	else if (game_infos->side == 0 && game_infos->ray_dir_x < 0)
		game_infos->texture = data->west;
	else if (game_infos->side == 1 && game_infos->ray_dir_y > 0)
		game_infos->texture = data->south;
	else if (game_infos->side == 1 && game_infos->ray_dir_y < 0)
		game_infos->texture = data->north;
	game_infos->tex_x = 0;
}

// fonction qui recupere le pixel de la texture a afficher
void	ft_get_good_pixel(t_data *data, t_game_infos *game_infos)
{
	if (game_infos->side == 0)
	{
		game_infos->wall_x = data->player->pos.y + game_infos->perp_wall_dist
			* game_infos->ray_dir_y;
		game_infos->tex_x = (int)(game_infos->wall_x
				* (float)game_infos->texture->width)
			% game_infos->texture->width;
	}
	else
	{
		game_infos->wall_x = data->player->pos.x + game_infos->perp_wall_dist
			* game_infos->ray_dir_x;
		game_infos->tex_x = (int)(game_infos->wall_x
				* (float)game_infos->texture->width)
			% game_infos->texture->width;
	}
}

// fonction qui dessine la ligne de pixel a afficher
void	ft_draw_textured_line(t_data *data, int x, t_game_infos *game_infos)
{
	int	tex_y;
	int	y;

	y = WIN_HEIGHT / 2 - game_infos->line_height / 2;
	game_infos->step = 0.0f;
	if (y < 0)
	{
		game_infos->step = -y * (1.0f * game_infos->texture->height
				/ game_infos->line_height);
		y = 0;
	}
	while (y < WIN_HEIGHT / 2 + game_infos->line_height / 2 && y < WIN_HEIGHT)
	{
		tex_y = (int)game_infos->step & (game_infos->texture->height - 1);
		game_infos->step += 1.0f * game_infos->texture->height
			/ game_infos->line_height;
		ft_put_pixel_to_image(data,
			x,
			y,
			game_infos->texture->data[tex_y][game_infos->tex_x]);
		y++;
	}
}
