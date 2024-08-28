/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:25:32 by kyeh              #+#    #+#             */
/*   Updated: 2024/08/28 17:01:55 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	multiple_quote(char *s, size_t quote1, size_t quote2)
{
	size_t	i;

	i = 0;
	if (!ft_strchr(s, '\'') && !ft_strchr(s, '\"'))
		return (' ');
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '\'')
			quote1++;
		if (s[i] == '\"')
			quote2++;
		i++;
	}
	if (quote1 % 2 || quote2 % 2)
	{
		if (!ft_strchr(s, '\''))
			return ('\"');
		else if (!ft_strchr(s, '\"'))
			return ('\'');
		else if (ft_charpos(s, '\'') < ft_charpos(s, '\"'))
			return ('\'');
		else
			return ('\"');
	}
	return ('s');
}

static char	set_quote(char *s, size_t i)
{
	char	quote;

	quote = ' ';
	if ((s + i)[0] == '\'' || (s + i)[0] == '\"')
		quote = (s + i)[0];
	else if (ft_strchr(s + i, '\'') || ft_strchr(s + i, '\"'))
	{
		if (!ft_strchr(s + i, '\''))
			quote = '\"';
		else if (!ft_strchr(s + i, '\"'))
			quote = '\'';
		else
		{
			if (ft_strchr(s + i, '\'') > ft_strchr(s + i, '\"'))
				quote = '\'';
			else
				quote = '\"';
		}
	}
	if (ft_charpos(s + i, quote) > ft_charpos(s + i, ' '))
		quote = ' ';
	return (quote);
}

static void	quote_fill(char *s, size_t *i, char quote)
{
	(*i)++;
	if (!s[*i])
		return ;
	*i += ft_charpos(s + *i, quote) + 1;
	if (!s[*i])
		return ;
	*i += ft_charpos(s + *i, quote);
	if (ft_strchr(s + *i, ' '))
		*i += ft_charpos(s + *i, ' ');
	else
		*i += ft_strlen(s + *i);
	(*i)--;
}

static char	utils(char **s, char quote, size_t *i, size_t *j)
{
	if (quote == 's')
	{
		if (ft_strchr(*s, '\''))
			quote = '\'';
		else
			quote = '\"';
		*s = ft_strclean(*s, "\'\"", 1);
	}
	quote = set_quote(*s, *i);
	if (quote == ' ')
	{
		if (ft_strchr(*s + *i, ' '))
			*i += ft_charpos(*s + *i, ' ');
		else
			*i += ft_strlen(*s + *i);
	}
	else
		quote_fill(*s, i, quote);
	if (ft_strchr(*s + *j, quote))
		if (!ft_charpos(*s + *j, quote))
			j++;
	*i -= (quote != ' ' && *s[*i - 1] == quote);
	return (quote);
}

char	**fill_cmd(char **cmd, char *s, size_t i, size_t k)
{
	size_t	j;
	char	quote;
	char	*tmp;

	while (s[i])
	{
		i += ft_count_whitespace(s + i);
		j = i;
		if (s[i] == 0)
			break ;
		quote = multiple_quote(s + i, 0, 0);
		if (quote != ' ' && quote != 's')
		{
			i += ft_charrpos(s + i, quote) + 1;
			tmp = ft_substr(s, j, i - j - 1);
			if (quote == '\'')
				cmd[k++] = ft_strclean(tmp, "\'", 1);
			if (quote == '\"')
				cmd[k++] = ft_strclean(tmp, "\"", 1);
			continue ;
		}
		quote = utils(&s, quote, &i, &j);
		cmd[k++] = ft_substr(s, j, i - j);
		i += (quote != ' ' && s[i] == quote);
	}
	free(s);
	return (cmd);
}
