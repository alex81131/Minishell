/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:45:26 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/13 11:45:26 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_welcome(void)
{
	ft_printf(YELLOW"\n################################################");
	ft_printf("################################\n\n");
	ft_printf(LIGHT_PINK"\n\t\t __  __ ___ _   _ ___ ____  _");
	ft_printf("   _ _____ _     _   \n");
	ft_printf(YELLOW"\t\t|  \\/  |_ _| \\ | |_ _/ ___|| | | | ");
	ft_printf("____| |   | |  \n");
	ft_printf(BLUE"\t\t| |\\/| || ||  \\| || |\\___ \\| |_| |  _");
	ft_printf("| | |   | |  \n");
	ft_printf(GREEN"\t\t| |  | || || |\\  || | ___) |  _  | |___|");
	ft_printf(" |___| |___ \n");
	ft_printf(""LIGHT_RED"\t\t|_|  |_|___|_| \\_|___|____/|_| |_|__");
	ft_printf("___|_____|_____|\n");
	ft_printf(YELLOW"\n\n\n########################################");
	ft_printf("###############");
	ft_printf("#########################\n\n"RESET);
	ft_printf("\tCreated by\t: kyeh & tkaragoz\n");
	ft_printf("\tGithub\t\t: https://github.com/alex81131/Minishell\n\n\n");
}

void	print_prompt(t_hash *env)
{
	if (sh()->hash->search(env, "PWD"))
	{
		ft_printf_fd(1, YELLOW_BOLD "%s: "DARK_BLUE"%s : " RESET, \
			sh()->hash->search(env, "USER"), \
			ft_strrchr(sh()->hash->search(env, "PWD"), '/'));
	}
	else
		ft_printf_fd(1, YELLOW_BOLD "%s: "DARK_BLUE"%s : " RESET, \
			sh()->hash->search(env, "USER"), NULL);
}
