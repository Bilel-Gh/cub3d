/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:08:56 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 14:33:03 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_remove_quote_and_comma(char *str)
{
	int		len;
	int		remove_char;
	char	*str_trim;

	len = ft_strlen(str);
	if (str[len - 1] == ',')
		remove_char = 3;
	else
		remove_char = 2;
	str_trim = ft_calloc(len - remove_char + 1, sizeof(char));
	if (!str_trim)
		return (NULL);
	ft_strncpy(str_trim, &str[1], len - remove_char);
	return (str_trim);
}

// fonction qui retoune la valeur numerique de la couleur
// en fonction du code rgb ou du nom de la couleur ou du code hexa
int	ft_get_xpm_value(char *line)
{
	int	value;

	value = 0;
	if (ft_strncmp(line, "#", 1) == 0)
		value = ft_atoi_base(&line[1], "0123456789ABCDEF");
	else if (ft_strncmp(line, "rgb", 3) == 0)
		value = ft_get_value_of_rgb_code(line);
	else
		value = ft_get_code_of_color_name(line);
	return (value);
}

// retourne la valeur num de la couleur qui correspond au charactere c
int	ft_get_color_value(t_xpm *xpm, char c, int nb_colors)
{
	int	i;

	i = 0;
	while (i < nb_colors)
	{
		if (xpm[i].character == c)
			return (xpm[i].value);
		i++;
	}
	return (0);
}

// gere le cas ou la couleur est sous format rgb dans le fichier xpm
int	ft_get_value_of_rgb_code(char *str)
{
	int	i;
	int	value;
	int	rgb[3];

	value = 0;
	i = 0;
	while (str[i] && !ft_isdigit(str[i]))
		i++;
	rgb[0] = ft_atoi(&str[i]);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && !ft_isdigit(str[i]))
		i++;
	rgb[1] = ft_atoi(&str[i]);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && !ft_isdigit(str[i]))
		i++;
	rgb[2] = ft_atoi(&str[i]);
	value = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	return (value);
}

// gere le cas ou la couleur est sous format nom dans le fichier xpm
int	ft_get_code_of_color_name(char *str)
{
	const char	*colors_name[] = {"black", "white", "red", "green", "blue",
		"yellow", "cyan", "magenta", "gray", "darkgray", "lightgray", "orange",
		"brown", "purple", "pink", "beige", "olive", "navy", "teal",
		"turquoise", "gold", "silver", "indigo", "maroon", "lime", "coral",
		"lavender", "salmon", "plum", "khaki", "orchid", "azure", "slategray"};
	const int	colors_value[] = {0x000000, 0xFFFFFF, 0xFF0000, 0x00FF00,
		0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF, 0x808080, 0x404040, 0xC0C0C0,
		0xFFA500, 0xA52A2A, 0x800080, 0xFFC0CB, 0xF5F5DC, 0x808000, 0x000080,
		0x008080, 0x40E0D0, 0xFFD700, 0xC0C0C0, 0x4B0082, 0x800000, 0x00FF00,
		0xFF7F50, 0xE6E6FA, 0xFA8072, 0xDDA0DD, 0xF0E68C, 0xDA70D6, 0xF0FFFF,
		0x708090};
	int			i;

	i = 0;
	ft_str_lowercase(str);
	while (i < 33)
	{
		if (ft_strncmp(str, colors_name[i], ft_strlen(colors_name[i])) == 0)
			return (colors_value[i]);
		i++;
	}
	return (0);
}
