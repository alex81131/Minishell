/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:11:56 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/11 15:11:56 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*arg_create(char *value)
{
	t_arg	*arg;
	char	*content;

	arg = (t_arg *)malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	content = ft_strdup(value);
	if (!content)
	{
		free(arg);
		return (NULL);
	}
	arg->value = content;
	arg->next = NULL;
	return (arg);
}

t_arg	*arg_last(t_arg *arg)
{
	while (arg->next)
		arg = arg->next;
	return (arg);
}

int	arg_add_back(t_arg **head, t_arg *new)
{
	if (!new)
		return (1);
	if (!*head)
		*head = new;
	else
		arg_last(*head)->next = new;
	return (0);
}

int	arg_lstsize(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg)
	{
		i++;
		arg = arg->next;
	}
	return (i);
}

void	arg_free(t_arg *arg)
{
	t_arg	*temp;

	while (arg)
	{
		temp = arg;
		if (arg->value)
			free(arg->value);
		arg = arg->next;
		free(temp);
	}
}
// arg: chained list of argument, storing their value
// typedef struct s_arg
// {
// 	char			*value;
// 	struct s_arg	*next;
// }	t_arg;
