/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:39:54 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/13 11:45:18 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}	t_arg;

typedef struct s_filename
{
	char				*name;
	t_token_type		type;
	struct s_filename	*next;
}	t_filename;

typedef struct s_cmd
{
	char			*name;
	t_arg			*arg;
	t_filename		*redirs;
	struct s_cmd	*next;
	int				fd_in;
	int				fd_out;
}	t_cmd;

int		pre_execution(t_sh *sh);
int		exec_cmd(t_sh *sh, char *cmd, t_arg *arg);
void	sh_free_all(t_sh *sh);
void	close_fd_p(int *fd);
void	close_fd_io(t_sh *sh);
int		handle_files(t_cmd *cmd);
void	unlink_heredocs(t_sh *sh);
int		ft_argsize(t_arg *arg);

#endif
