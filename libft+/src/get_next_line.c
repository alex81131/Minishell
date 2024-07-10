/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:38:15 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/10 18:15:38 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_next_line(char **s)
{
	char	*out;
	char	*tmp;
	size_t	len;

	len = 0;
	out = NULL;
	while ((*s)[len] != '\n' && (*s)[len])
		len++;
	if ((*s)[len] == '\n')
	{
		out = ft_substr(*s, 0, len + 1);
		tmp = ft_strdup(*s + len + 1);
		free(*s);
		*s = tmp;
		if (!**s)
		{
			free(*s);
			*s = NULL;
		}
		return (out);
	}
	out = ft_strdup(*s);
	free(*s);
	*s = NULL;
	return (out);
}

static char	*check_and_return(char **s, ssize_t n, int fd)
{
	if (n < 0)
		return (NULL);
	if (!n && (!s[fd] || !*s[fd]))
		return (NULL);
	return (return_next_line(&s[fd]));
}

char	*get_next_line(int fd)
{
	char		*tmp;
	char		*buf;
	static char	*s[FOPEN_MAX];
	ssize_t		n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	n = read(fd, buf, BUFFER_SIZE);
	while (n > 0)
	{
		buf[n] = '\0';
		if (!s[fd])
			s[fd] = ft_strdup("");
		tmp = ft_strjoin(s[fd], buf);
		free(s[fd]);
		s[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
		n = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (check_and_return(s, n, fd));
}
/*
In check_and_return:
	The condition (!s[fd] || !*s[fd]) checks if the buffer for the given
	file descriptor fd is NULL or empty.

In return_next_line:
	out = ft_substr(*s, 0, len + 1);
	tmp = ft_strdup(*s + len + 1);

	*s			*s+len
	0	1	2	\n		3			len = 3
						tmp

The +1 in ft_substr is to include the \n
(len + 1 is the total length to be copied);
the +1 in ft_strdup is to start after the \n
(len + 1 is the starting point after \n).
*/