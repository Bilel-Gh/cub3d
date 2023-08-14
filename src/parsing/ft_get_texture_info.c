/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_texture_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:09:00 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 14:47:46 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// fonction qui recupere l'entete de la texture
// et qui stocke les infos dans la structure texture
// l4entete est de la forme "width height nb_colors nchars"
// avec nchars = 1 qu'on ne va pas trop utiliser normalement
// grace a l'entete on peut recup la taille de la texture et le nb de couleurs
// on va aussi allouer la memoire pour le tableau de structure xpm
// qui va contenir les infos pr chaque couleurs du fichier xpm
int	ft_get_xpm_entete_info(t_texture *texture, t_xpm **xpm,
	int *nb_colors, char *line)
{
	char	*line_entete;
	int		i;

	line_entete = ft_remove_quote_and_comma(line);
	if (!line_entete)
		return (ft_error(ERROR_MALLOC));
	i = 0;
	texture->width = ft_atoi(&line_entete[i]);
	while (line_entete[i] != '\0' && line_entete[i] != ' ')
		i++;
	i++;
	texture->height = ft_atoi(&line_entete[i]);
	while (line_entete[i] != '\0' && line_entete[i] != ' ')
		i++;
	i++;
	*nb_colors = ft_atoi(&line_entete[i]);
	ft_free((void **)&line_entete);
	*xpm = (t_xpm *)ft_calloc(*nb_colors + 1, sizeof(t_xpm));
	if (!*xpm)
		return (ft_error(ERROR_MALLOC));
	return (EXIT_SUCCESS);
}

// fonciton qui recupere les infos sur les couleurs de la texture
// on va stocker les infos dans la structure xpm
// on recupere la valeur de la couleur et le caractere associe
int	ft_get_xpm_color(t_xpm *xpm, char **file_content, int nb_color)
{
	int		i;
	char	*line_color;

	i = 0;
	line_color = NULL;
	while (i < nb_color)
	{
		line_color = ft_remove_quote_and_comma(file_content[i]);
		if (!line_color)
			return (ft_error(ERROR_MALLOC));
		if (ft_strlen(line_color) != 0)
		{
			xpm[i].character = line_color[0];
			if (ft_strlen(line_color) > 4)
				xpm[i].value = ft_get_xpm_value(&line_color[4]);
			else
				return (ft_error(ERROR_XPM_COLOR));
			ft_free((void **)&line_color);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// fonction qui va recuperer pour chaque ligne de la texture
// la valeur de la couleur associee de chaque pixel
// on va stocker les valeurs dans la structure texture dans le tableau data
int	ft_create_texture_data(t_texture *texture, t_xpm *xpm,
	char **file_content, int nb_colors)
{
	int		i;
	int		j;
	char	*line_texture;

	i = 0;
	while (i < texture->height && file_content[i])
	{
		line_texture = ft_remove_quote_and_comma(file_content[i]);
		if (!line_texture)
			return (ft_error(ERROR_MALLOC));
		if (ft_strlen(line_texture) != 0)
		{
			j = 0;
			while (j < texture->width && line_texture[j] != '\0')
			{
				texture->data[i][j] = ft_get_color_value(xpm, line_texture[j],
						nb_colors);
				j++;
			}
			ft_free((void **)&line_texture);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// fonction qui va allouer la memoire pour la matrice de la texture
// et set a 0 les valeurs de la matrice
int	ft_calloc_texture_data(t_texture *texture)
{
	int	i;

	texture->data = (int **)ft_calloc(texture->height, sizeof(int *));
	if (!texture->data)
		return (ft_error(ERROR_MALLOC));
	i = 0;
	while (i < texture->height)
	{
		texture->data[i] = (int *)ft_calloc(texture->width, sizeof(int));
		if (!texture->data[i])
			return (ft_free_tabs(texture->data, i), ft_error(ERROR_MALLOC));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_get_texture_info(t_texture *texture, char **file_content)
{
	const int	nb_line = ft_count_nb_line(file_content);
	const char	*xpm_strs[] = {"/* columns rows colors chars-per-pixel */",
		"/* pixels */"};
	int			i;
	int			nb_colors;
	t_xpm		*xpm;

	nb_colors = 0;
	xpm = NULL;
	i = 0;
	while (file_content[i] && ft_strcmp(file_content[i], xpm_strs[0]))
		i++;
	if (i >= nb_line || i + 1 >= nb_line || i + 2 >= nb_line)
		return (ft_error("Error\nTexture bad syntax\n"));
	if (ft_get_xpm_entete_info(texture, &xpm, &nb_colors, file_content[++i])
		|| ft_get_xpm_color(xpm, &file_content[++i], nb_colors))
		return (ft_free((void **)&xpm), EXIT_FAILURE);
	while (file_content[i] && ft_strcmp(file_content[i], xpm_strs[1]))
		i++;
	if (i >= nb_line || i + 1 >= nb_line)
		return (free(xpm), ft_error("Error\nTexture bad syntax\n"));
	if (ft_calloc_texture_data(texture)
		|| ft_create_texture_data(texture, xpm, &file_content[++i], nb_colors))
		return (free(xpm), EXIT_FAILURE);
	return (free(xpm), EXIT_SUCCESS);
}
