/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_border.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:09:21 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 15:17:41 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// fonction qui check si toute les cases d'une ligne verticale
// sont bien inncaessible par le joueur
// si une case est accessible la map est donc pas fermée
int	check_vertical_line_closed(int x, int y, int map_height, int **valide_case)
{
	while (y < map_height)
	{
		if (valide_case[y][x] == true)
			return (ft_error("Error\nMap pas fermée\n"));
		y++;
	}
	return (EXIT_SUCCESS);
}

// fonction qui check si toute les cases d'une ligne horizontale
// sont bien inncaessible par le joueur
// si une case est accessible la map est donc pas fermée
int	check_horizontal_line_closed(int x, int y, int map_width, int **valide_case)
{
	while (x < map_width)
	{
		if (valide_case[y][x] == true)
			return (ft_error("Error\nMap map pas fermée\n"));
		x++;
	}
	return (EXIT_SUCCESS);
}

// check que le joueur ne peut pas se deplacer sur une case vide
int	move_in_empty_case(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			if (map->map[y][x] == EMPTY && map->valide_case[y][x] == true)
				return (ft_error("Error\nle joueur peut se \
					deplacer sur une case vide\n"));
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

// fonction qui check si la map est correctement fermée
int	ft_check_map_border(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	if (check_horizontal_line_closed(x, y, map->x_max, map->valide_case))
		return (EXIT_FAILURE);
	y = map->y_max - 1;
	x = 0;
	if (check_horizontal_line_closed(x, y, map->x_max,
			map->valide_case) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	x = 0;
	y = 0;
	if (check_vertical_line_closed(x, y, map->y_max,
			map->valide_case) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	x = map->x_max - 1;
	y = 0;
	if (check_vertical_line_closed(x, y, map->y_max,
			map->valide_case) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (move_in_empty_case(map))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
