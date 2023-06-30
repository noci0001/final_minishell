/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:42:42 by snocita           #+#    #+#             */
/*   Updated: 2023/06/30 18:43:36 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// MINISHELL NAME
# define MINISHELL_NAME "\033[32mMinishelly\033[0m"

//CHECK IF TO LEAVE
# define EMPTY 0
# define CMD 1
# define FLAG 2
# define ARG 3
# define TRUNC 4
# define APPEND 5
# define INPUT 6
# define PIPE 7
# define END 8

# define SKIP 1
# define NOSKIP 0

// LIBFT
# include "../libft/libft.h"
// # include "libreadline.h"
# include <readline/readline.h>
# include <readline/history.h>
// readline, rl_clear_history, rl_on_new_line,
//	rl_replace_line, rl_redisplay, add_history
# include <stdio.h>
// printf
# include <stdlib.h>
// malloc, free
# include <unistd.h>
// write, access, open, read, close,
//	dup, dup2, pipe, isatty, ttyname,
//	ttyslot, ioctl
# include <sys/types.h>
// fork, wait, waitpid, wait3, wait4
# include <signal.h>
// kill, exit
# include <sys/stat.h>
// getcwd, chdir, stat, lstat, fstat, unlink,
// errono macro
# include <errno.h>
//	execve
# include <dirent.h>
// opendir, readdir, closedir
# include <string.h>
// strerror, perror
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
// tcsetattr, tcgetattr, tgetent,
//	tgetflag, tgetnum, tgetstr, tgoto, tputs: termios.h
typedef struct s_cmd	t_cmd;

typedef struct s_token
{
    char			*str;
    int				type;
    struct s_token *prev;
    struct s_token *next;
} t_token;

struct s_cmd
{
	t_token	*start;
	char	**evnp;
	int		exit;
	int		ret;
};

typedef struct s_valid
{
	int		spaces;
	int		path;
	char	*env;
	char	**splitted_env;
	char	*tmp1;
	char	*tmp2;
}	t_valid;

t_cmd	*create_linked_list(char *input);
t_cmd	*malloc_node(void);
void	free_double_arr(char **str);
t_cmd	*lexing(char *block, t_cmd *curr);
int		check_redirection_arg(char *word, int redirection);
int		is_red(char *str);
void	redirection_in(char *str);
void	redirection_out(char *str);
void	here_doc(char *str);
void	double_redirection(char *str);
char	**allocate_args(char **words_of_program, int i);
int		ft_env(char	**g_my_envp);
int		ft_pwd(char	**g_my_envp);
int		ft_export(t_token	*token);
char	**obtain_double_array(char **double_array);
char	**obtain_envp(char **envp);
char	*check_string_to_export(char	*to_export);
void	ft_debug(void);
void	debug_write(char *str, int id);
void	debug_token_interception(char *token, int	token_type);
char	*get_time(void);
void	create_header(void);
void	debug_get_full_input(char *str);
void	debug_get_sectioned_input(char *str);
void	print_linked(t_cmd *head);
void	update_envp(char	*value_to_add);
void	update_envp_pwd(char **g_my_envp, char *new_pwd);
int		check_line(t_cmd *cmd, t_token *token);
int 	ft_echo(t_token *token);
int		ft_cd(t_cmd	*input_struct, char **g_my_envp);
int		check_nb_args(char **args);
char	*ft_get_env(char	**envp, char	*value_to_fetch);
char	*get_value_before_equal(char	*str);
void	remove_quote(char **cmd);
char	*delete_quote_tok(char *tok);
char	*apply_delete(char *tok, int *i);
void    parse(char	*line, t_cmd *cmd);
int     quote_check(t_cmd *cmd, char **line);
int     quotes(char *line, int index);
char    *space_line(char *line);
char    *space_alloc(char *line);
int		is_sep(char *line, int i);
t_token	*get_tokens(char *line);
void	ft_skip_space(const char *str, int *i);
int		ignore_sep(char *line, int i);
t_token	*next_token(char *line, int *i);
void	type_arg(t_token *token, int separator);
void	squish_args(t_cmd *cmd);
t_token	*prev_sep(t_token *token, int skip);
int		is_type(t_token *token, int type);
int		is_types(t_token *token, char *types);
int		is_last_valid_arg(t_token *token);
void	free_token(t_token *start);
void    print_double_array(char **str);

#endif