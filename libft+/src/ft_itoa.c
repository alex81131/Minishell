/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:44:25 by kyeh              #+#    #+#             */
/*   Updated: 2024/08/13 18:49:21 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_digit(int n)
{
	int	digit;

	digit = 0;
	if (n <= 0)
		digit++;
	while (n != 0)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

char	*ft_inttochar(char *str, unsigned int m, unsigned int len)
{
	if (m == 0)
		str[0] = '0';
	while (m > 0)
	{
		str[len--] = (m % 10) + 48;
		m /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		len;
	unsigned int	m;

	len = ft_digit(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		m = n * -1;
	}
	else
		m = n;
	str = ft_inttochar(str, m, len);
	return (str);
}
/*
// int → long int:
// Type promotion is safe and does not result in any loss of data
// because a long int can represent all the values that an int can, and more.
//
//ww -I. -o ft_itoa Non-standard\ functions/ft_itoa.c
int	main(int ac, char **av)
{
	(void) ac;
	printf("ft_itoa: %s\n", ft_itoa(atoi(av[1])));
	return (0);
}
*/