/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:47:02 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/11 14:47:02 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_filename	*fn_create(char *path, t_token_type type)
{
	t_filename	*filename;
	char		*new_path;

	filename = (t_filename *)malloc(sizeof(t_filename));
	if (!filename)
		return (NULL);
	new_path = ft_strdup(path);
	if (!new_path)
	{
		free(filename);
		return (NULL);
	}
	filename->path = new_path;
	filename->type = type;
	filename->next = NULL;
	return (filename);
}

t_filename	*fn_last(t_filename *filename)
{
	while (filename->next)
		filename = filename->next;
	return (filename);
}

int	fn_add_back(t_filename **head, t_filename *new)
{
	if (!new)
		return (1);
	if (!*head)
		*head = new;
	else
		fn_last(*head)->next = new;
	return (0);
}

int	fn_lstsize(t_filename *filename)
{
	int	i;

	i = 0;
	while (filename)
	{
		i++;
		filename = filename->next;
	}
	return (i);
}

void	fn_free(t_filename *filename)
{
	t_filename	*temp;

	while (filename)
	{
		temp = filename;
		if (filename->path)
			free(filename->path);
		filename = filename->next;
		free(temp);
	}
}
// filename: chained list of in/outfile, heredoc, append, storing their path
// typedef struct s_filename
// {
// 	char				*path;
// 	t_token_type		type;
// 	struct s_filename	*next;
// }	t_filename;