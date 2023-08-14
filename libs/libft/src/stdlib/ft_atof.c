/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:24:17 by bghandri          #+#    #+#             */
/*   Updated: 2023/07/26 18:48:30 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_stdlib.h"

double	ft_atof(const char *nptr)
{
	double	res;
	double	dec;
	int		sign;

	res = 0;
	dec = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign = -1;
	while (ft_isdigit(*nptr))
		res = res * 10 + (*nptr++ - '0');
	if (*nptr++ == '.')
	{
		while (ft_isdigit(*nptr))
		{
			dec = dec * 10 + (*nptr++ - '0');
			res *= 10;
		}
	}
	return ((res + dec) * sign);
}
