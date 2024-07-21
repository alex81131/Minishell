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

static char	dont_replace_quotes(char *s, size_t *i)
{
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
	}
	if (s[*i])
		return (1);
	else
		return (0);
}

static void	assign_value(char **value, char *var)
{
	if (var && var[0] == '?')
		*value = ft_itoa(sh()->question_mark);
	else
		*value = sh()->env->search(sh()->env, var);
}

char	*fill_str_with_var(char *s, size_t i, size_t j, char *var)
{
	char	*value;

	while (s[i])
	{
		if (!dont_replace_quotes(s, &i))
			break ;
		if (s[++i] == '$')
		{
			j = ++i;
			while (s[i] && s[j] != '\"' && s[j] != ' ' && s[j] != '$')
				j++;
			var = ft_substr(s, i, j - i);
			assign_value(&value, var);
			if (value)
			{
				s = ft_insert(s, value, i - 1, ft_strlen(var) + 1);
				i += ft_strlen(value) - 1;
			}
			else
				s = ft_insert(s, " ", i - 1, ft_strlen(var) + 1);
			free_string(&var);
		}
	}
	return (s);
}
/*
Changed from if (s[i] == '$') to if (s[++i] == '$') to correctly walk pass $.

[Variable Expansion]:
Replace any shell variables (like $VAR) with their corresponding values.
*/