/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:37:30 by kyeh              #+#    #+#             */
/*   Updated: 2024/06/21 15:37:30 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	err_exit(const char *err, const char *msg)
{
	ft_printf_fd(STDERR_FILENO, "%s: %s\n", err, msg);
	exit(EXIT_FAILURE);
}

void	perror_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_tolower_char(char *c)
{
	*c = ft_tolower(*c);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
