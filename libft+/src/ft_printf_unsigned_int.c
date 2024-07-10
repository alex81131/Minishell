/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:57:09 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/10 18:15:59 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_udigit(unsigned int n)
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

char	*ft_uitoa(unsigned int n)
{
	char			*str;
	unsigned int	len;

	len = ft_udigit(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	str = ft_inttochar(str, n, len);
	return (str);
}

int	ft_uputnbr(unsigned int n)
{
	int		len;
	char	*nb;

	nb = ft_uitoa(n);
	len = ft_putstr(nb);
	free(nb);
	return (len);
}
