/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number_hex_fd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:13:02 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/10 18:15:57 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_hex_fd(unsigned int n, const char format, int fd)
{
	if (n < 16)
	{
		if (n < 10)
			ft_putchar_fd(n + '0', fd);
		else
		{
			if (format == 'x')
				ft_putchar_fd(n - 10 + 'a', fd);
			if (format == 'X')
				ft_putchar_fd(n - 10 + 'A', fd);
		}
	}
	else
	{
		ft_put_hex_fd(n / 16, format, fd);
		ft_put_hex_fd(n % 16, format, fd);
	}
}

int	ft_puthex_fd(unsigned int n, const char format, int fd)
{
	if (n == 0)
		return (write(fd, "0", 1));
	else
		ft_put_hex_fd(n, format, fd);
	return (hex_digit(n));
}
