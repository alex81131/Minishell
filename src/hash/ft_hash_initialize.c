/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_initialize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:27:47 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/13 12:27:47 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash	*ft_hash_initialize(void)
{
	static t_hash	hash;

	hash.before = NULL;
	hash.next = NULL;
	hash.del = ft_hashdel;
	hash.print = ft_hash_display;
	hash.add_back = ft_hash_addback;
	hash.add_front = ft_hash_addfront;
	hash.del_all = ft_hash_free;
	hash.search = ft_hash_search_value;
	hash.len = ft_hashlen;
	hash.change = ft_hash_change_value;
	hash.new = ft_hashnew;
	hash.sort_key = ft_hash_sort_key;
	hash.rsort_key = ft_hash_revsort_key;
	hash.sort_val = ft_hash_sort_value;
	hash.rsort_val = ft_hash_revsort_value;
	hash.find = ft_hash_find;
	return (&hash);
}
