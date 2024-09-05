/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_sort_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:27:42 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/17 14:27:42 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hash_sort_key(t_hash **hash)
{
	t_hash	temp;
	t_hash	*node;

	if (!hash || !*hash)
		return ;
	node = *hash;
	while (node->next)
	{
		if (ft_strcmp(node->key, node->next->key) > 0)
		{
			temp.key = node->key;
			temp.value = node->value;
			node->key = node->next->key;
			node->value = node->next->value;
			node->next->key = temp.key;
			node->next->value = temp.value;
			node = *hash;
		}
		node = node->next;
	}
}

void	ft_hash_sort_value(t_hash **hash)
{
	t_hash	temp;
	t_hash	*node;

	if (!hash || !*hash)
		return ;
	node = *hash;
	while (node->next)
	{
		if (ft_strcmp(node->value, node->next->value) > 0)
		{
			temp.key = node->key;
			temp.value = node->value;
			node->key = node->next->key;
			node->value = node->next->value;
			node->next->key = temp.key;
			node->next->value = temp.value;
			node = *hash;
		}
		node = node->next;
	}
}

void	ft_hash_revsort_key(t_hash **hash)
{
	t_hash	temp;
	t_hash	*node;

	if (!hash || !*hash)
		return ;
	node = *hash;
	while (node->next)
	{
		if (ft_strcmp(node->key, node->next->key) < 0)
		{
			temp.key = node->key;
			temp.value = node->value;
			node->key = node->next->key;
			node->value = node->next->value;
			node->next->key = temp.key;
			node->next->value = temp.value;
			node = *hash;
		}
		node = node->next;
	}
}

void	ft_hash_revsort_value(t_hash **hash)
{
	t_hash	temp;
	t_hash	*node;

	if (!hash || !*hash)
		return ;
	node = *hash;
	while (node->next)
	{
		if (ft_strcmp(node->value, node->next->value) < 0)
		{
			temp.key = node->key;
			temp.value = node->value;
			node->key = node->next->key;
			node->value = node->next->value;
			node->next->key = temp.key;
			node->next->value = temp.value;
			node = *hash;
		}
		node = node->next;
	}
}
