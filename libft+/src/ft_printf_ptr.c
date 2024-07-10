/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:07:13 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/10 18:15:58 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ptr_digit(uintptr_t n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

void	ft_put_ptr(uintptr_t n)
{
	if (n < 16)
	{
		if (n < 10)
			ft_putchar(n + '0');
		else
			ft_putchar(n - 10 + 'a');
	}
	else
	{
		ft_put_ptr(n / 16);
		ft_put_ptr(n % 16);
	}
}

int	ft_putptr(uintptr_t ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		len += write(1, "(nil)", 5);
	else
	{
		len += write(1, "0x", 2);
		ft_put_ptr(ptr);
		len += ptr_digit(ptr);
	}
	return (len);
}
/*
uintptr_t is an unsigned integer type that is capable of storing a pointer.
The hexadecimal format is a convention used for representing
and displaying these addresses because it is more compact and readable
than other numerical representations, especially for large numbers.

"write" not only displays the content, but also returns the characters printed.
*/