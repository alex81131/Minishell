/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:30:15 by kyeh              #+#    #+#             */
/*   Updated: 2024/06/27 14:04:41 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	starting_point(const char *str)
{
	int	i;
	int	count;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	count = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			count++;
		i++;
	}
	return (i);
}

static int	negative(const char *str)
{
	int	i;
	int	count;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	count = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			count++;
		i++;
	}
	return (count);
}

static int	error(const char *base)
{
	int	i;
	int	j;

	i = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-'
			|| base[i] <= 32 || base[i] >= 127)
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

static int	base_index(char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *str, const char *base)
{
	int	i;
	int	j;
	int	result;

	result = 0;
	if (error(base) > 1)
	{
		i = starting_point(str);
		j = base_index(str[i], base);
		while (j >= 0)
		{
			result = result * error(base) + j;
			i++;
			j = base_index(str[i], base);
		}
		if (negative(str) % 2 == 1)
			result *= -1;
	}
	return (result);
}
/*
//Need to deal with white spaces first, and then +-, and then number.
//If finding white spaces after +-, return 0
#include <stdio.h>

int		main(void)
{
	printf("%d\n", ft_atoi_base("	+++++--133742", "0123456789"));
	printf("%d\n", ft_atoi_base("	     ---101010", "01"));
	printf("%d\n\n", ft_atoi_base(" 	+---539", "0123456789abcdef"));
	printf("%d\n", ft_atoi_base("   -+--+012ab567", "0123456789"));
	printf("%d\n", ft_atoi_base("   -+--+ 012ab567", "0123456789"));
	printf("%d\n", ft_atoi_base("   -+--+Z012ab567", "0123456789"));
	printf("%d\n", ft_atoi_base("   -+--+012 ab567", "0123456789"));
}
*/
