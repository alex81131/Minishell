/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:54:32 by kyeh              #+#    #+#             */
/*   Updated: 2024/06/27 16:16:41 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		len;
	char	*nb;

	nb = ft_itoa(n);
	len = ft_putstr_fd(nb, fd);
	free(nb);
	return (len);
}
/*
void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}

//ww -I. Non-standard\ functions/ft_putnbr_fd.c
//Non-standard\ functions/ft_itoa.c Non-standard\ functions/ft_putstr_fd.c
//Non-standard\ functions/ft_putchar_fd.c
int	main(int ac, char **av)
{
	(void) ac;

	ft_putnbr_fd(atoi(av[1]), 1);
	return (0);
}
*/