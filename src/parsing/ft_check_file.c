/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:07:40 by bghandri          #+#    #+#             */
/*   Updated: 2023/08/14 15:19:59 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// verifie l'extension du fichier
int	check_file_extension(char *file_name, int type_of_ext)
{
	int			len;
	const char	*ext[] = {".cub", ".xpm"};

	len = ft_strlen(file_name);
	if (len < 5)
		return (ft_error("Error\n nom de fichier trop court\n"));
	len -= 4;
	if (ft_strncmp(file_name + len, ext[type_of_ext], 4))
	{
		if (type_of_ext == CUB)
			return (ft_error("Error\n l'extension du fichier n'est pas .cub\n"));
		else if (type_of_ext == XPM)
			return (ft_error("Error\n l'extension du fichier n'est pas .xpm\n"));
	}
	return (EXIT_SUCCESS);
}

// verifie que le fichier existe et est accessible et qu'il a la bonne extension
int	ft_check_file(char *file_name, int *fd, int type_of_ext)
{
	if (check_file_extension(file_name, type_of_ext))
		return (EXIT_FAILURE);
	*fd = open(file_name, O_RDONLY);
	if (*fd == -1)
		return (ft_error("Error\n le fichier n'existe pas ou \
				n'est pas accessible\n"));
	return (EXIT_SUCCESS);
}
