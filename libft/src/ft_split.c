/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:35:49 by kyeh              #+#    #+#             */
/*   Updated: 2024/06/27 15:57:27 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_count(const char *s, char c)
{
	size_t	len;
	size_t	i;
	int		count;

	i = 0;
	len = ft_strlen(s);
	count = 0;
	while (s[i] && i < len)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_strdup_len(const char *str, int len)
{
	char	*s;

	s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_memcpy(s, str, len);
	s[len] = '\0';
	return (s);
}

void	free_array_len(char **array, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(array[i++]);
	free(array);
}

static char	**split_action(char const *s, char c, char **array)
{
	size_t		i;
	size_t		j;

	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			i = 0;
			while (*(s + i) && *(s + i) != c)
				i++;
			array[j] = ft_strdup_len(s, i);
			if (!array[j])
			{
				free_array_len(array, j);
				return (NULL);
			}
			j++;
			s += i;
		}
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char		**array;
	int			count;

	count = str_count(s, c);
	array = (char **)malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = split_action(s, c, array);
	return (array);
}
/*
//cc:
//ww -I. -o ft_split
// Non-standard\ functions/ft_split.c string.h/ft_strlen.c string.h/ft_memcpy.c
//./ft_split "Include0headers0000and0link0functions00are00new0\!0" "0" | cat -e
int	main(int argc, char **argv)
{
	int	i;
	char	**separated;
	(void)	argc;

	separated = ft_split(argv[1], argv[2][0]);
	if (!separated)
		return (0);
	i = -1;
	while (separated[++i])
	{
		printf("%s\n", separated[i]);
		free(separated[i]);
	}
	free(separated);
	return (0);
}
*/