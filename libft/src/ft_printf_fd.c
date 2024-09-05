/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:42:57 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/10 18:15:56 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_uputnbr_fd(unsigned int n, int fd)
{
	int		len;
	char	*nb;

	nb = ft_uitoa(n);
	len = ft_putstr_fd(nb, fd);
	free(nb);
	return (len);
}

int	ft_input_printf_fd(va_list vl, const char format, int fd)
{
	int	n;

	n = 0;
	if (format == 'c')
		n += ft_putchar_fd(va_arg(vl, int), fd);
	else if (format == 's')
		n += ft_putstr_fd(va_arg(vl, char *), fd);
	else if (format == 'p')
		n += ft_putptr_fd(va_arg(vl, uintptr_t), fd);
	else if (format == 'd' || format == 'i')
		n += ft_putnbr_fd(va_arg(vl, int), fd);
	else if (format == 'u')
		n += ft_uputnbr_fd(va_arg(vl, unsigned int), fd);
	else if (format == 'x' || format == 'X')
		n += ft_puthex_fd(va_arg(vl, unsigned int), format, fd);
	else if (format == '%')
		n += ft_putchar_fd('%', fd);
	return (n);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		i;
	va_list	vl;
	int		char_printed;

	i = 0;
	char_printed = 0;
	va_start(vl, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			char_printed += ft_input_printf_fd(vl, format[i + 1], fd);
			i++;
		}
		else
			char_printed += ft_putchar_fd(format[i], fd);
		i++;
	}
	va_end(vl);
	return (char_printed);
}
