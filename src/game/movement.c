/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:37:57 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/11 18:33:06 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_is_movement_key(int keycode)
{
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		return (1);
	return (0);
}

// fonction fait tourner la camera (la direction et le plan) vers la gauche
void	ft_rotate_cam_left(t_data *data)
{
	float	old_dir_x;
	float	old_plan_x;

	old_dir_x = data->player->dir.x;
	data->player->dir.x = data->player->dir.x * cos(-RADIAN)
		- data->player->dir.y * sin(-RADIAN);
	data->player->dir.y = old_dir_x * sin(-RADIAN) + data->player->dir.y
		* cos(-RADIAN);
	old_plan_x = data->player->plan.x;
	data->player->plan.x = data->player->plan.x * cos(-RADIAN)
		- data->player->plan.y * sin(-RADIAN);
	data->player->plan.y = old_plan_x * sin(-RADIAN)
		+ data->player->plan.y * cos(-RADIAN);
}

// fonction fait tourner la camera (la direction et le plan) vers la droite
// on utilise une formule trigonometrique pour
//	de direction et le vecteur de plan en 2D
// la formule est: x' = x * cos(a) - y * sin(a) et y' = x * sin(a) + y * cos(a)
// cette formule permet de faire tourner un vecteur de a radian
//	dans le sens trigonometrique en 2D
// l'unite radian est une unite de mesure d'angle
// 	qui permet de faire des calculs plus facilement qu'avec les degres
void	ft_rotate_cam_right(t_data *data)
{
	float	old_dir_x;
	float	old_plan_x;

	old_dir_x = data->player->dir.x;
	old_plan_x = data->player->plan.x;
	data->player->dir.x = data->player->dir.x * cos(RADIAN)
		- data->player->dir.y * sin(RADIAN);
	data->player->dir.y = old_dir_x * sin(RADIAN) + data->player->dir.y
		* cos(RADIAN);
	data->player->plan.x = data->player->plan.x * cos(RADIAN)
		- data->player->plan.y * sin(RADIAN);
	data->player->plan.y = old_plan_x * sin(RADIAN) + data->player->plan.y
		* cos(RADIAN);
}

bool	is_collision(t_data *data, float x, float y, float size)
{
	t_direction	dir;
	int			i;
	int			j;

	dir.left = (int)(x - size);
	dir.right = (int)(x + size);
	dir.top = (int)(y - size);
	dir.bottom = (int)(y + size);
	i = dir.top;
	while (i <= dir.bottom)
	{
		j = dir.left;
		while (j <= dir.right)
		{
			if (data->map[i][j] == '1')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

// fonction qui gere les deplacements du joueur
// le vecteur de plan est perpendiculaire au vecteur de direction
// il permet de se deplacer sur les cotes en fonction de la bonne direction
// ex: si le joueur regarde vers le haut (dir.x = 0, dir.y = -1)
// alors le vecteur de plan est vers la gauche (plan.x = -1, plan.y = 0)
// pour aller sur un coté, il suffit d'ajouter ou de soustraire
//	 le vecteur de plan au vecteur de position
void	ft_move_player(t_data *data, int keycode)
{
	t_vector	new_pos;

	new_pos = (t_vector){data->player->pos.x, data->player->pos.y};
	if (keycode == W)
	{
		new_pos.x += data->player->dir.x * MOVE_SPEED;
		new_pos.y += data->player->dir.y * MOVE_SPEED;
	}
	else if (keycode == S)
	{
		new_pos.x -= data->player->dir.x * MOVE_SPEED;
		new_pos.y -= data->player->dir.y * MOVE_SPEED;
	}
	else if (keycode == A)
	{
		new_pos.x -= data->player->plan.x * MOVE_SPEED;
		new_pos.y -= data->player->plan.y * MOVE_SPEED;
	}
	else if (keycode == D)
	{
		new_pos.x += data->player->plan.x * MOVE_SPEED;
		new_pos.y += data->player->plan.y * MOVE_SPEED;
	}
	if (!is_collision(data, new_pos.x, new_pos.y, PLAYER_SIZE))
		data->player->pos = new_pos;
}
