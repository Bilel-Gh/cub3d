/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_newline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:08:38 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 14:15:19 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// fonction qui compte le nombre de caractere avant le \n
static int	ft_strlen_before_newline(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && str[len] != '\n')
		len++;
	return (len);
}

// fonction qui compte le nombre de \n dans une string
static int	count_nb_newline(char *str)
{
	int	i;
	int	nb_endl;

	i = 0;
	nb_endl = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			nb_endl++;
		i++;
	}
	return (nb_endl + 1);
}

// fonction qui split une string en fonction des \n
// prend en compte les ligne avec juste un \n et les lignes vides
char	**ft_split_newline(char *str)
{
	char	**strs;
	int		i;
	int		j;

	strs = (char **)ft_calloc(count_nb_newline(str) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (str[j])
	{
		strs[i] = ft_substr(str, j, ft_strlen_before_newline(&str[j]));
		if (!strs[i])
			return (ft_free_strs_n(strs, i), NULL);
		i++;
		j += ft_strlen_before_newline(&str[j]);
		if (!str[j])
			break ;
		j++;
	}
	strs[i] = NULL;
	return (strs);
}
