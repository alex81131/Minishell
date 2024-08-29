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
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

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

//	STRUCTURE
typedef struct		s_hash
{
	char			*key;
	void			*value;
	// char			*type;
	struct s_hash	*top;
	struct s_hash	*before;
	struct s_hash	*next;
	struct s_hash	*(*new)(char *, void *, char *);
	void			(*add_front)(struct s_hash **, struct s_hash *);
	void			(*add_back)(struct s_hash **, struct s_hash *);
	void			(*del)(struct s_hash **, struct s_hash *, struct s_hash *);
	void			(*del_all)(struct s_hash **);
	void			*(*search)(struct s_hash *, char *);
	struct s_hash	*(*find)(struct s_hash *, char *);
	void			(*change)(struct s_hash *, char *, void *, char *);
	size_t			(*len)(struct s_hash *);
	void			(*print)(struct s_hash *, char *);
	void			(*sort_key)(struct s_hash **);
	void			(*rsort_key)(struct s_hash **);
	void			(*sort_val)(struct s_hash **);
	void			(*rsort_val)(struct s_hash **);
}					t_hash;

typedef struct		s_strhash
{
	char	*key;
	char	*value;
}					t_strhash;

typedef struct	s_sh
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
}				t_sh;

//	HASH
t_hash		*ft_hash_initialize(void);
t_hash		*ft_hashnew(char *key, void *value, char *type);
void		ft_hash_addfront(t_hash **hash, t_hash *new);
void		ft_hash_addback(t_hash **hash, t_hash *new);
void		ft_hashdel(t_hash **hash, t_hash *before, t_hash *next);
void		ft_hash_free(t_hash **hash);
void		*ft_hash_search_value(t_hash *hash, char *key);
t_hash		*ft_hash_find(t_hash *hash, char *key);
void		ft_hash_change_value(t_hash *hash, char *key, \
								void *value, char *type);
size_t		ft_hashlen(t_hash *hash);
void		ft_hash_display(t_hash *hash, char *name);
void		ft_hash_sort_key(t_hash **hash);
void		ft_hash_sort_value(t_hash **hash);
void		ft_hash_revsort_key(t_hash **hash);
void		ft_hash_revsort_value(t_hash **hash);

//	EXEC, BUILTIN
void		change_sh_path(t_hash *env, t_hash *hash);
int			is_builtin(char *cmd);
void		builtin_env(t_sh *sh, t_hash *env);
void		builtin_unset(t_sh *sh, char **key, size_t j);
void		builtin_echo(char **cmd);
void		builtin_cd(t_sh *sh, char **cmd);
void		builtin_export(t_sh *sh, char **key);

void		ft_exec(size_t i);
void		get_env_var(t_sh *sh, char **env, size_t i);

//	SIGNAL
void		handle_sigint(int sig);
void		child_sigint(int sig);

//	PARSING, include in_quote and if_escaped in libft+
int			analyzer(char *str, char *tok, size_t i);
char		parsing(char *line);
char		*fill_str_with_var(char *s, size_t i, size_t pos);
int			quote_error(char *str);

char		*operator(char *s, size_t *i, size_t *j, size_t n);
int			in_quote(char *s, size_t i);
int			if_escaped(char *s, size_t i);
size_t		operator_counter(char *s, size_t i, size_t block);

char		**parse(char *str);
char		**fill_cmd(char **cmd, char *s, size_t i, size_t k);
char		*double_quote_allocator(char **s, size_t *j);
char		*simple_quote_allocator(char *s, size_t *j);
char		*non_special_allocator(char **s, size_t *j);
char		*quote_checker(char *s, size_t quote, size_t dquote);

//	DISPLAY
void		print_prompt(t_hash *hash);
void		print_welcome(void);

//	REDIRECTIONS
void		redirection(size_t i, int in_fd);
void		redirect(int oldfd, int newfd);
void		final_redir(size_t i, int in_fd);
int			lonely_command(size_t i, int in_fd);
void		left_redir(size_t *i);
void		right_redir(size_t *i);

//	UTILS
t_sh		*sh(void);
void		free_string(char **arr);
size_t		ft_arrlen(char **arr);
char		**ft_arrjoin(char **a1, char **a2);
void		ft_exit(int exit_code, int i);
size_t		ft_charpos(const char *str, int c);
size_t		ft_charrpos(const char *str, int c);
size_t		ft_count_whitespace(const char *str);
char		*ft_insert(char *src, char *insert, size_t start, size_t skip);
void		ft_memdel(void **ptr);
char		**ft_split_minishell(char *buff);
char		*ft_strclean(char *str, const char *charset, int free);
char		*ft_strjoin_free(char *s1, char *s2, int option);
size_t		ft_sublen(const char *s1, const char *s2, int existence);
char		*ft_strtok(char *str, const char *separator);
void		skip_quote_char(char *s, size_t *i, size_t *pos, char *charset);
void		skip_quote(char *str, size_t *i, char c);

#endif