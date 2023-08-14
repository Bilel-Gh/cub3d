/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:51:39 by bghandri          #+#    #+#             */
/*   Updated: 2023/07/30 10:42:35 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_libft.h"
#include "ft_string.h"

//affiche une chaine de caractere et retourne sa longueur
int	print_str_fd(char *str, int fd)
{
	int	len;

	if (!str)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	len = ft_strlen(str);
	write(fd, str, len);
	return (len);
}

// affiche un nombre et retourn sa longueur
int	print_nbr_fd(int nbr, int fd)
{
	char	*str;
	int		len;

	str = ft_itoa(nbr);
	len = print_str_fd(str, fd);
	free(str);
	return (len);
}

// print arg au bon format et retourne sa longueur
int	get_format(int fd, va_list args, const char format)
{
	int	len_print;

	len_print = 0;
	if (format == 'c')
		len_print += ft_putchar_fd(va_arg(args, int), fd);
	else if (format == 's')
		len_print += print_str_fd(va_arg(args, char *), fd);
	else if (format == 'd' || format == 'i')
		len_print += print_nbr_fd(va_arg(args, int), fd);
	return (len_print);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		res;

	i = 0;
	res = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]))
		{
			res += get_format(fd, args, format[i + 1]);
			i++;
		}
		else
			res += ft_putchar_fd(format[i], fd);
		i++;
	}
	va_end(args);
	return (res);
}
