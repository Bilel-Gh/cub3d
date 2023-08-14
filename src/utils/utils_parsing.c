/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:08:44 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 14:14:20 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_str_lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isupper(str[i]))
			str[i] = ft_tolower(str[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	if (!str || !base)
		return (-1);
	if (ft_strlen(base) < 2)
		return (-1);
	while (ft_isspace(str[i]))
		i++;
	while (str[i] && ft_strchr(base, str[i]))
	{
		nb = nb * ft_strlen(base) + (ft_strchr(base, str[i]) - base);
		i++;
	}
	return (nb);
}

// fonction qui verifie si la map ne contient pas de ligne vide
int	is_invalid_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\0')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_get_nb_infos_recup(int *is_infos_found)
{
	int	i;
	int	nb_infos_recup;

	i = 0;
	nb_infos_recup = 0;
	while (i < 6)
	{
		if (is_infos_found[i] == true)
			nb_infos_recup++;
		i++;
	}
	return (nb_infos_recup);
}
