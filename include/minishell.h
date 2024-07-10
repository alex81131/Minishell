/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:45:43 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/10 17:45:43 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

typedef struct		s_sh
{
	char		**key;
	char		**value;
	char		***cmd;
	char		**path;
	t_hash		*hash;
	t_hash		*env;
	t_hash		*add;
	char		printed;
	short		question_mark;
	char		*redir;
	int			fd[2];
	char		*target_file;
	int			stdin_bkp;
}					t_sh;

/*
** EXEC CMD
*/

void				exec_cmd(t_sh *sh, char **cmd);
int					ft_fork_process(t_sh *sh, char **cmd);
void				ft_exec(size_t i);
void				replace_question_mark(char **cmd);

/*
** BUILTIN
*/

void				builtin_export(t_sh *sh, char **key);
void				exec_builtin(t_sh *sh, size_t j);
void				builtin_env(t_sh *sh, t_hash *env);
void				builtin_cd(t_sh *sh, char **cmd);
void				get_env_var(t_sh *sh, char **env, size_t i);
void				replace_env_var(t_sh *sh, char **cmd, size_t i);
void				builtin_echo(char **cmd);
void				builtin_unset(t_sh *sh, char **key, size_t j);
int					is_builtin(char *cmd);

/*
** SIGNAL
*/

void				handle_sigint(int sig);
void				child_sigint(int sig);

/*
** PARSING
*/

char				parsing(char *str);
char				***alloc_commands(char *str, size_t *nb);
size_t				bloc_counter(char *s, size_t i, size_t block);
char				**parse(char *s);
char				**fill_cmd(char *s, char **cmd, size_t i, size_t j);
char				*double_quote_allocator(char **s, size_t *j);
char				*simple_quote_allocator(char *s, size_t *j);
char				*non_special_allocator(char **s, size_t *j);
char				*quote_checker(char *s, size_t quote, size_t dquote);
size_t				separator_counter(char *s, size_t i, size_t block);
void				quotes_splitter(char *s, size_t *i, char c);
char				*complete_cmd(char *s, char c);
char				*found_redir(char *s, size_t *j, size_t *i, size_t nb);
size_t				separator_counter(char *s, size_t i, size_t block);
int					analyser(char *str, char *tok, size_t i);
int					quotes_error(char *s);
char				*fill_str_with_var(char *s, size_t i, size_t j, char *var);
char				*join_quotes(char *s, size_t i, size_t j);
char				**fill_cmd(char *s, char **cmd, size_t i, size_t j);

/*
** DISPLAY
*/

void				print_prompt(t_hash *hash);
void				printf_welcome(void);

/*
** REDIRECTIONS
*/

void				ft_pipe(int i, int in_fd);
void				redirections(int i, int in_fd);
void				redir_counter(void);
void				right_redir(int *i);
int					lonely_command(int i, int in_fd);
void				redirect(int oldfd, int newfd);
void				left_redir(int *i);
void				final_redir(int i, int in_fd);

/*
** UTILS
*/

void				ft_exit(int exit_code, int i);
void				change_sh_path(t_hash *env, t_hash *hash);
t_sh				*sh(void);

#endif