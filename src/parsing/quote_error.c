/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:58:34 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/20 17:58:34 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_quote_error(void)
{
	ft_printf_fd(2, "minishell: parse error: quotes not completed\n");
	return (EXIT_FAILURE);
}

static char	next_quote(char *str, size_t i)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (str[i]);
		i++;
	}
	return (0);
}

int	quote_error(char *str)
{
	size_t	i;
	char	quote;

	if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (EXIT_SUCCESS);
	quote = '\"';
	if (ft_strchr(str, '\'') && \
		(ft_strchr(str, '\'') < ft_strchr(str, '\"') || !ft_strchr(str, '\"')))
		quote = '\'';
	i += ft_charpos(s, quote) + 1;
	if (!str[i])
		return (print_quote_error());
	while (str[i])
	{
		if (ft_strchr(str + i, quote))
			i += ft_charpos(str + i, quote) + 1;
		else
			return (print_quote_error());
		if (!str[i])
			break ;
		quote = next_quote(str, i);
		i += ft_charpos(str + i, quote) + 1;
	}
	return (EXIT_SUCCESS);
}
