/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:02:54 by bghandri          #+#    #+#             */
/*   Updated: 2023/07/26 18:48:30 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_putnbr_base_fd(unsigned long long n, int fd, const char *base);
int	ft_putstr_fd(char *s, int fd);

int	ft_putptr_fd(unsigned long long ptr, int fd)
{
	int	ret;

	ret = 0;
	ret += ft_putstr_fd("0x", fd);
	ret += ft_putnbr_base_fd(ptr, fd, "0123456789abcdef");
	return (ret);
}
