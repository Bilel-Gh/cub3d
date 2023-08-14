/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bghandri <bghandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:02:43 by bghandri          #+#    #+#             */
/*   Updated: 2023/07/26 18:48:30 by bghandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_putchar_fd(char c, int fd);
int	ft_putnbr_base_fd(unsigned long long n, int fd, const char *base);

int	ft_putnbr_fd(int n, int fd)
{
	int	ret;

	ret = 0;
	if (n < 0)
	{
		ret += ft_putchar_fd('-', fd);
		n *= -1;
	}
	ret += ft_putnbr_base_fd(n, fd, "0123456789");
	return (ret);
}
