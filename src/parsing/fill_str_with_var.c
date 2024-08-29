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

static char	dont_replace_quote(char *s, size_t *i)
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

static void	assign_value(char **s, size_t *i, size_t *j)
{
	char	*var;
	char	*value;

	var = ft_substr(*s, *i, *j - *i);
	if (!var)
		return ;
	if (var && var[0] == '?')
		value = ft_itoa(sh()->question_mark);
	else
		value = sh()->env->search(sh()->env, var);
	if (value)
	{
		*s = ft_insert(*s, value, *i - 1, ft_strlen(var) + 1);
		*i += ft_strlen(value) - 1;
		free(value);
	}
	else
		*s = ft_insert(*s, " ", *j, ft_strlen(var) + 1);
	free(var);
}

char	*fill_str_with_var(char *s, size_t i, size_t j)
{
	while (s[i])
	{
		if (!dont_replace_quote(s, &i))
			break ;
		if (s[i] && s[i] == '$')
		{
			j = ++i;
			while (s[j] && s[j] != '\"' && s[j] != ' ' && s[j] != '$')
				j++;
			assign_value(&s, &i, &j);
		}
		else
			i++;
	}
	return (s);
}
/*
[Variable Expansion]:
Replace any shell variables (like $VAR) with their corresponding values.
*/