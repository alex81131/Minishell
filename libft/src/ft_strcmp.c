/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:13:03 by kyeh              #+#    #+#             */
/*   Updated: 2024/02/12 13:13:05 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*If 2 strings are different, s1[i] - s2[i] automatically doesn't give 0.
Not 0: compare the ASCII of the characterof the 2 strings*/
int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
/*
#include <stdio.h>

int	main()
{
	printf("%d\n", ft_strcmp("a", "aufdhaf"));
	return (0);
}
*/
