/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:30:40 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/18 13:30:40 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	sig_initiate(void);
void	sig_heredoc(int status);
void	sig_exec(int status);

#endif
