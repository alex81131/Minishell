/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:42:57 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/10 18:16:01 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_input_printf(va_list vl, const char format)
{
	int	n;

	n = 0;
	if (format == 'c')
		n += ft_putchar(va_arg(vl, int));
	else if (format == 's')
		n += ft_putstr(va_arg(vl, char *));
	else if (format == 'p')
		n += ft_putptr(va_arg(vl, uintptr_t));
	else if (format == 'd' || format == 'i')
		n += ft_putnbr(va_arg(vl, int));
	else if (format == 'u')
		n += ft_uputnbr(va_arg(vl, unsigned int));
	else if (format == 'x' || format == 'X')
		n += ft_puthex(va_arg(vl, unsigned int), format);
	else if (format == '%')
		n += ft_putchar('%');
	return (n);
}

int	ft_printf(const char *format, ...)
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
			char_printed += ft_input_printf(vl, format[i + 1]);
			i++;
		}
		else
			char_printed += ft_putchar(format[i]);
		i++;
	}
	va_end(vl);
	return (char_printed);
}
/*
//Careful with ptr = NULL:
//ww *.c -o test -L.
#include <stdio.h>

int	main(void)
{
	int	i;
	int	j;

	i = ft_printf(" %p %p ", (void *)0, (void *)0);
	ft_printf("\nWord count = %d\n", i);
	j = printf(" %p %p ", (void *)0, (void *)0);
	printf("\nWord count = %d\n", j);
	return (0);
}
*/
/*
The standard putchar function in C takes an int as its argument
and returns an int.
So as to:
1. Handle EndOfFile constant, which is an integer.
2. Characters in C are essentially small integers.
   They are promoted to int when used in expressions or passed to functions
   with variadic parameters (like printf).
3. the character codes might exceed the range of a char
   (especially an unsigned char).

<stdarg.h>
va_list
	A type that represents a list of variable arguments
	that always goes with functions declared with ellipsis:
	ft_prinft(const char *f, ...)
va_start(va_list, start_after):
	Initializes a va_list
	start_after: the last argument before the variable arguments
	to be stored in va_list
va_arg(va_list, *type*):
	Retrieves arguments in va_list:
va_end(va_list):
	Cleans up stuff
Could write char_printed += ft_input(vl, format[i++ + 1]);
but it's slightly confusing

And to printf %, use % to escape the type indication: %%
*/