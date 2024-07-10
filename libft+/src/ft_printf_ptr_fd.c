/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:07:13 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/10 18:15:58 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_ptr_fd(uintptr_t n, int fd)
{
	if (n < 16)
	{
		if (n < 10)
			ft_putchar_fd(n + '0', fd);
		else
			ft_putchar_fd(n - 10 + 'a', fd);
	}
	else
	{
		ft_put_ptr_fd(n / 16, fd);
		ft_put_ptr_fd(n % 16, fd);
	}
}

int	ft_putptr_fd(uintptr_t ptr, int fd)
{
	int	len;

	len = 0;
	if (ptr == 0)
		len += write(fd, "(nil)", 5);
	else
	{
		len += write(fd, "0x", 2);
		ft_put_ptr_fd(ptr, fd);
		len += ptr_digit(ptr);
	}
	return (len);
}
