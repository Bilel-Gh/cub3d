/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:07:51 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 14:13:24 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game.h"
#include "parsing.h"
#include <mlx_int.h>

void	ft_init_main(t_data *data, t_player *player, t_texture *texture)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(player, sizeof(t_player));
	ft_bzero(texture, sizeof(t_texture) * 4);
	data->north = &texture[0];
	data->south = &texture[1];
	data->east = &texture[2];
	data->west = &texture[3];
	data->player = player;
}

int	main(int ac, char **av)
{
	t_data		data;
	t_player	player;
	t_texture	texture[4];

	ft_init_main(&data, &player, texture);
	if (ac != 2)
		return (ft_fprintf(STDERR, "Error\n nombre d'argument invalide\n"));
	if (ft_parsing(&data, av[1]))
		return (ft_free_data_s(&data), EXIT_FAILURE);
	if (ft_init_and_start_game(&data))
		ft_error("Error\n probleme lors du lancement du jeu\n");
	ft_free_data_s(&data);
	return (0);
}
