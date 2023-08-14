/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:02:14 by bghandri          #+#    #+#             */
/*   Updated: 2023/07/26 18:48:30 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_putnbr_base_fd(unsigned long long n, int fd, const char *base);

int	ft_puthex_fd(unsigned int n, int fd, int upper_case)
{
	if (upper_case)
		return (ft_putnbr_base_fd(n, fd, "0123456789ABCDEF"));
	else
		return (ft_putnbr_base_fd(n, fd, "0123456789abcdef"));
}
