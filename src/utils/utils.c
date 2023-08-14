/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:08:49 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 14:13:33 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_vector(t_vector *vector, float x, float y)
{
	vector->x = x;
	vector->y = y;
}

int	ft_count_nb_line(char **files)
{
	int	nb_line;

	nb_line = 0;
	while (files[nb_line])
		nb_line++;
	return (nb_line);
}

// ecrit sur la sortie d'erreur et retourne EXIT_FAILURE
int	ft_error(char *str)
{
	ft_putstr_fd(str, STDERR);
	return (EXIT_FAILURE);
}

void	ft_close(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}
