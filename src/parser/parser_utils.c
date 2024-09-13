/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:25:30 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/13 16:29:10 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ps_check_all_null(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		if (token->value)
			i = 0;
		token = token->next;
	}
	return (i);
}

char	*ps_strjoin(char *s1, char *s2)
{
	char	*new;

	if (!s1 && !s2)
		return (NULL);
	else if (!s2)
		return (s1);
	else if (!s1)
		return (ft_strdup(s2));
	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}
