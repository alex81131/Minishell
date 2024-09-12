/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:39:54 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/12 15:44:04 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

int	pre_execution(t_sh *sh);
int	exec_cmd(t_sh *sh, char *cmd, t_args *args);
void	free_all_sh(t_sh *sh);
void	close_fd_p(int *fd);
void	close_fd_io(t_sh *sh);
int	handle_files(t_cmd *cmd);
void	unlink_heredocs(t_sh *sh);

#endif
