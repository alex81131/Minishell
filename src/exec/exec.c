/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:00:17 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/10 19:05:13 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	handle_files(t_cmd *cmd)
{
	t_filenames	*tmp;

	tmp = cmd->redirs;
	while (tmp)
	{
		redir_files(cmd, tmp);
		if (cmd->fd_in == -1 || cmd->fd_out == -1)
			return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}


void	redir_files(t_cmd *cmd, t_filenames *file)
{
	if (file->type == INFILE || file->type == N_HEREDOC)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close (cmd->fd_in);
		cmd->fd_in = open(file->name, O_RDONLY);
		if (cmd->fd_in == -1)
			ft_printf_fd(STDERR_FILENO, "Minishell: %s: %s\n", file->name, strerror(errno));
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else
	{
		if (cmd->fd_out != STDOUT_FILENO)
			close (cmd->fd_out);
		if (file->type == OUTFILE)
			cmd->fd_out = open (file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->type == APPEND)
			cmd->fd_out = open (file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fd_out == -1)
			ft_printf_fd(STDERR_FILENO, "Minishell: %s: %s\n", file->name, strerror(errno));
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}



void	child_process(t_sh *sh, t_cmd *cmd)
{
	int	fd_p[2];

	fd_p[0] = -1;
	fd_p[1] = -1;
	if (cmd->next && pipe(fd_p) == -1)
	{
		ft_printf_fd("Minishell: %s\n", strerror(errno));
		exit(2);
	}
	//signal(SIGIT, sig_exec);
	sh->pids[sh->pid_count] = fork();
	if (sh->pids[sh->pid_count] == -1)
	{
		ft_printf_fd("Minishell: %s\n", strerror(errno));
		exit(3);
	}
	else if (!sh->pids[sh->pid_count])
		post_child_process(sh, cmd, fd_p);
	else
		dup2(fd_p[0], STDIN_FILENO);
	close_fd_p(fd_p);
}

void	post_child_process(t_sh *sh, t_cmd *cmd, int *fd_p)
{
	int	exit_code;

	exit_code = 0;
	//signal(SIGQUIT, SIG_DFL);
	if (cmd->next && cmd->fd_out == STDOUT_FILENO)
		dup2(fd_p[1], STDOUT_FILENO);
	if (handle_files(cmd))
	{
		close_fd_io(sh);
		close_all_fdp(fd_p);
		free_all_sh(sh);
		exit(EXIT_FAILURE);
	}
	close_fd_io(sh);
	close_all_fdp(fd_p);
	if (is_builtin(sh->cmd))
	{
		exit_code = exec_builtin(sh, cmd->name, cmd->args);
		free_all_sh(sh);
		exit(exit_code);
	}
	exit_code = exec_cmd(sh, cmd->name, cmd->args);
	free_all_sh(sh);
	//if (exit_code == -2)
	//	exit(IS_A_DIRECTORY);
	//exit(COMMAND_NOT_FOUND);
}

void wait_processes(t_sh *sh)
{
	int	status;
	int	i;

	i = 0;
	while (i < sh->pid_count)
	{
		if (waitpid(sh->pids[i], &status, 0))
		{
			if (WIFEXITED(status))
			{
				//g_signals.signal_code = 0;
				//sh->exit_code = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				// if (WTERMSIG(status) == SIGQUIT)
				// 	ft_printf_fd(2, "[%d]: Quit (core dumped)\n", sh->pids[i]);
				// g_signals.signal_code = SIGNAL_OFFSET + WTERMSIG(status);
			}
		}
		i++;
	}
	unlink_heredocs(sh);
}



int	execution(t_sh *sh)
{
	t_cmd	*tmp;

	tmp = sh->cmd;
	if (tmp->next == NULL && is_builtin(tmp->name))
	{
		if (handle_files(tmp))
			return ((sh->exit_code = 1), EXIT_FAILURE);
		if (is_builtin(tmp->name) == 2)
			ft_printf_fd(2, "exit\n");
		unlink_heredocs(sh);
		sh->exit_code = exec_builtin(sh, tmp->name, tmp->args);
		return (EXIT_SUCCESS);
	}
	while (tmp)
	{
		child_process(sh, tmp);
		sh->pid_count++;
		tmp = tmp->next;
	}
	wait_processes(sh);
	return (EXIT_SUCCESS);
}

int	pre_execution(t_sh *sh)
{
	sh->fd_in = dup(STDIN_FILENO);
	sh->fd_out = dup(STDOUT_FILENO);

	execution(sh);

	dup2(sh->fd_in, STDIN_FILENO);
	close(sh->fd_in);
	dup2(sh->fd_out, STDOUT_FILENO);
	close(sh->fd_out);

	return (EXIT_SUCCESS);
}


