/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:26:11 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/06 16:27:57 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* echo "$12345" -> be careful of this
* echo "$<abcdef" -> too
* echo "$/?lol" -> too
*/

static int	ps_count_var(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == '$')
			count++;
	return (count);
}

static char	ps_convert_var(char *str, char *var, t_sh *sh)
{
	char	*before_env;
	char	*env_var;
	char	*after_env;
	char	*res;

	before_env = ps_get_before_env(str, var);
	if (!before_env)
		return (NULL);
	env_var = ps_get_env_var(var + 1, sh);
	after_env = ps_get_after_env(var + 1);
	if (!after_env)
		return (free(before_env), free(env_var), NULL);
	res = ft_strjoin_free(before_env, env_var, 1);
	if (!res)
		return (free(after_env), NULL);
	res = ft_strjoin_free(res, after_env, 1);
	if (env_var)
		free(env_var);
	return (free(after_env), res);
}

/*
* Try with a non-working only path for ex: `$sdofijsdf`
* could restructure this part to this:
* check if env var exists, if not just remove it from the string
* if it does exist: transform it with getenv
* ft_strjoin before the env var, put env, and strjoin after the env var
*/

static int	ps_handle_var(t_token *token)
{
	char	*temp;
	char	*var;
	char	*res;
	int		n;

	n = ps_count_var(token->value);
	while (token->value)
	{
		var = ft_strchr(token->value, '$');
		if (!var || n == 0)
			break ;
		if (ft_strcmp(var, "$"))
			break ;
		temp = token->value;
		res = ps_convert_var(token->value, var, token->sh);
		if (res && res[0] == '\0')
		{
			free(res);
			res = NULL;
		}
		token->value = res;
		free(temp);
		n--;
	}
	return (0);
}

/*
* token->value could be NULL!!
*/

int	ps_expand_variables(t_token *token)
{
	while (token)
	{
		if (token->type == STRING || token->type == DOUBLEQUOTE)
			ps_handle_var(token);
		token = token->next;
	}
	return (0);
}

// t_token	*ps_split_tokens(t_token *token, char *str)
// {
// 	t_token	*tmp;
// 	t_token	*local;
// 	char	**words;
// 	int		i;

// 	i = 0;
// 	local = NULL;
// 	if (str == NULL)
// 		return (NULL);
// 	words = ft_split2(str, " \t\n");
// 	if (words == NULL)
// 		return (local);
// 	while (words[i])
// 	{
// 		tmp = tok_create(words[i], ft_strlen(words[i]), STRING, token->ctx);
// 		tok_add_back(&(local), tmp);
// 		free(words[i]);
// 		i++;
// 	}
// 	free(words);
// 	return (local);
// }

// int	ps_replace_current(t_token *current, t_token *new)
// {
// 	t_token	*current_next;
// 	t_token	*new_tmp;
// 	char	*current_value;

// 	if (!current || !new)
// 		return (0);
// 	// temps
// 	current_value = current->value;
// 	current_next = current->next;

// 	//assignation
// 	tok_last(new)->next = current_next;
// 	current->value = new->value;
// 	current->next = new->next;

// 	new_tmp = new;
// 	new_tmp->value = NULL;
// 	new_tmp->next = NULL;

// 	// very end
// 	tok_free_one(new_tmp);
// 	free(current_value);
// 	return (0);
// }