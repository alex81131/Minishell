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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "builtins.h"
# include "builder.h"
# include "signals.h"
# include "env.h"

//	COLORS
# define BLUE "\033[0;38;5;123m"
# define LIGHT_PINK "\033[0;38;5;200m"
# define PINK "\033[0;38;5;198m"
# define DARK_BLUE "\033[1;38;5;110m"
# define GREEN "\033[1;32m"
# define LIGHT_GREEN "\033[0;38;5;121m"
# define LIGHT_RED "\033[0;31;5;110m"
# define FLASH_GREEN "\033[33;32m"
# define WHITE_BOLD "\033[37m"
# define GREY "\033[3;90m"
# define ORANGE "\033[3;91m"
# define YELLOW "\033[0;33m"
# define YELLOW_BOLD "\033[1;33m"
# define RESET   "\033[0m"
# define WHITESPACE " \t\n\v\f\r"

# define P_NAME "Minishell"
# define ESC_START "\001"
# define ESC_END "\002"

# define IS_A_DIRECTORY 126
# define COMMAND_NOT_FOUND 127
# define SIGNAL_OFFSET 128

# define RND_BASIS 14695981039346656037UL
# define RND_PRIME 1099511628211UL

# define PROMPT "\001\033[1;38;5;110m\002Minishell: \001\033[0m\002"
# define DEF_ENV "SHELL=Minishell"

//	STRUCTURE

typedef struct s_sh
{
	int				fd_in;
	int				fd_out;
	char			exit_code;
	int				cmd_count;
	pid_t			*pids;
	int				pid_count;
	t_cmd			*cmd;
	t_env			*env;
}	t_sh;

typedef struct s_signal
{
	int				end_heredoc;
	int				signal_code;
}	t_signal;

extern t_signal	g_signals;

//	main + utils
t_sh	*init_sh(char **env);
void	sh_free_token(t_sh *sh, t_token *token);
void	sh_free_all(t_sh *sh);
t_env	*ms_env_dup(char **env);
// void	*ms_free_double(char **value);
// t_env	*ms_getenv(char *path, t_env *env);

//	t_env
// t_env	*env_create(char *id, char *value, char *raw);
// t_env	*env_default_env(void);
// void	env_del_one(t_env *env);
// void	env_free(t_env *env);
// int		env_add_back(t_env **head, t_env *new);
// char	*env_get_id(char *raw);
// char	*env_get_value(char *raw);
// int		env_lstsize(t_env *env);

#endif
