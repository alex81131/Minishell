/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_str_with_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:24:53 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/20 16:24:53 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_value(char **s, size_t *i, size_t pos)
{
	char	*var;
	char	*value;

	var = ft_substr(*s, pos + 1, *i - pos - 1);
	if (!var)
		return ;
	if (var && var[0] == '?')
		value = ft_itoa(sh()->question_mark);
	else
		value = sh()->env->search(sh()->env, var);
	if (value)
	{
		*s = ft_insert(*s, value, pos, ft_strlen(var) + 1);
		*i += ft_strlen(value) - 1;
		free(value);
	}
	else
		*s = ft_insert(*s, " ", pos, ft_strlen(var) + 1);
	free(var);
}

char	*fill_str_with_var(char *s, size_t i, size_t pos)
{
	size_t	len;

	len = ft_strlen(s);
	while (i < len)
	{
		skip_quote_char(s, &i, &pos, WHITESPACE);
		if (s[i] && s[i] == '$')
		{
			pos = i++;
			while (s[i] && !if_escaped(s, i) \
					&& !ft_strchr(" \t\n\v\f\r;|<>$", s[i]))
				i++;
			assign_value(&s, &i, pos);
		}
		else
			i++;
	}
	return (s);
}
/*
Changed from if (s[i] == '$') to if (s[++i] == '$') to correctly walk pass $.

[Variable Expansion]:
Replace any shell variables (like $VAR) with their corresponding values.
*/