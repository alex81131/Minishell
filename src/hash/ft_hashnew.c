/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:45:43 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/13 12:45:43 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*value_alloc(void *value, char *type)
{
	if (!ft_strcmp(type, "string"))
		return (ft_strdup(value));
	return (NULL);
}

t_hash	*ft_hashnew(char *key, void *value, char *type)
{
	t_hash	*hash;

	hash = (t_hash *)malloc(sizeof(t_hash));
	if (!hash)
		return (NULL);
	hash->key = ft_strdup(key);
	hash->value = value_alloc(value, type);
	// hash->type = type;
	hash->top = hash;
	hash->before = NULL;
	hash->next = NULL;
	hash->add_front = ft_hash_addfront;
	hash->add_back = ft_hash_addback;
	hash->del = ft_hashdel;
	hash->del_all = ft_hash_free;
	hash->search = ft_hash_search_value;
	hash->find = ft_hash_find;
	hash->change = ft_hash_change_value;
	hash->len = ft_hashlen;
	hash->print = ft_hash_display;
	hash->sort_key = ft_hash_sort_key;
	hash->rsort_key = ft_hash_revsort_key;
	hash->sort_val = ft_hash_sort_value;
	hash->rsort_val = ft_hash_revsort_value;
	return (hash);
}
// Maybe value can hold data of other types?