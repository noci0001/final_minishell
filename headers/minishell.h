/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:42:42 by snocita           #+#    #+#             */
/*   Updated: 2023/07/10 10:00:56 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// MINISHELL NAME
# define MINISHELL_NAME "\033[32mMinishelly\033[0m"

# define BUFF_SIZE 4096 

# define UNSET 0
# define EXPORT 1

//ERROR CODES
# define SUCCESS 0
# define GENERALERROR 1
# define MISUSEOFBUILTINS 2
# define CANNOTEXECUTE 126
# define COMMANDNOTFOUND 127

//CHECK IF TO LEAVE
# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3 
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define HEREDOC 7

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
# include <fcntl.h>
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
# include <sys/wait.h>
// tcsetattr, tcgetattr, tgetent,
//	tgetflag, tgetnum, tgetstr, tgoto, tputs: termios.h
typedef struct s_cmd	t_cmd;

typedef struct s_token
{
	char			*str;
	int				type;
	int				exp_disabled;
	char			*path;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key_value[2];
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

struct s_cmd
{
	t_token	*start;
	t_env	*env;
	t_env	*exit_code;
	int		exit;
	int		ret;
	char	*input;
};

typedef struct s_valid
{
	int				spaces;
	int				path;
	struct s_env	*env;
	char			**splitted_env;
	char			*tmp1;
	char			*tmp2;
}					t_valid;

void	init_struct(int ac, char **av, char **envp, t_cmd *cmd);
int		obtain_envp(t_cmd	*cmd, char **envp);
void	add_key_value(t_env	*env);
void	parse(char	*line, t_cmd *cmd);
int		quote_check(t_cmd *cmd, char **line);
char	*space_line(char *line);
char	*space_alloc(char *line);
void	squish_args(t_cmd *cmd);
t_token	*prev_sep(t_token *token, int skip);
int		is_type(t_token *token, int type);
int		is_types(t_token *token, char *types);
int		is_last_valid_arg(t_token *token);
int		check_line(t_cmd *cmd, t_token *token);		
int		is_builtin(t_cmd	*cmd);
int		ft_echo(t_token *token, t_cmd	*cmd, t_env	*env);
int		ft_cd(t_cmd	*cmd, t_env	*env);
int		ft_env(t_env *env);
int		ft_pwd(t_env	*env);
int		ft_unset(t_cmd *cmd, t_env *env);
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
int		ft_export(t_cmd	*cmd, t_env	*envp);
char	**obtain_double_array(char **double_array);
char	*check_string_to_export(char	*to_export);
void	ft_debug(void);
void	debug_write(char *str, int id);
void	debug_token_interception(char *token, int token_type);
char	*get_time(void);
void	create_header(void);
void	debug_get_full_input(char *str);
void	debug_get_sectioned_input(char *str);
void	print_linked(t_cmd *head);
void	update_envp(char	*value_to_add);
void	update_envp_pwd(char **g_my_envp, char *new_pwd);
int		check_nb_args(char **args);
char	*ft_get_env(t_env *env, char *value_to_fetch);
char	*get_value_before_equal(char	*str);
void	remove_quote(char **cmd);
char	*delete_quote_tok(char *tok);
char	*apply_delete(char *tok, int *i);
int		quotes(char *line, int index);
t_token	*get_tokens(char *line);
void	ft_skip_space(const char *str, int *i);
int		ignore_sep(char *line, int i);
t_token	*next_token(char *line, int *i);
void	type_arg(t_token *token, int separator);
void	free_token(t_token *start);
void	print_double_array(char **str);
int		check_for_duplicates(char	*to_export);
void	free_env(t_env *env);
void	execution(t_cmd	*cmd, t_token	*token);
char	**cmd_tab(t_token *start);
void	program_exit(t_cmd	*cmd);
int		run_cmd(char **args, t_env *env, t_cmd	*cmd);
int		cmd_validation(t_cmd *cmd);
char	*env_to_str_func(t_env *lst);
size_t	size_env(t_env *lst);
void	free_tab(char **tab);
int		free_env_list(t_env *env);
int		arg_absent(t_cmd	*cmd, t_env	*envp, int check);
t_env	*is_inside_envp(t_env	*envp, t_cmd	*cmd, int check, char	*str);
void	redirection_in(char *str);
void	redirection_out(char *str);
void	double_redirection(char *str);
void	here_doc(char *str);
int		is_arg_absent(t_cmd	*cmd, t_env	*envp, int check);
void	check_expansion(t_cmd	*cmd, t_token	*token);
char	*expansion_string(t_cmd	*cmd, char	*str, int index);
void	increase_shlvl(t_env	*env, t_cmd	*cmd);
int		update_pwd(t_env	*env);
void	update_oldpwd(t_env	*env, char	*old_cwd);
int		navigate_home(t_env	*env, int is_tilde, t_cmd	*cmd);
int		navigate_forward(t_env	*env, char	*arg);
int		navigate_backward(t_env	*env);
void	sig_c(int signal);
void	sig_d(int signal);
void	sig_handler(void);
void	signal_inprocess(void);
void	turn_off_echo(void);
int		go_places(char	*arg, t_env	*env);
void	redirection_handler(t_token *token);
int		loop_through_tokens(t_token	*token);
int		is_last_valid_arg(t_token *token);
char	*space_line(char *line);
char	*space_alloc(char *line);
t_token	*loop_through_line(char *line, int index);
int		next_alloc(char *line, int *i);
char	*get_value_from_before_equal(char	*str, int index);
int		unexpected_token_message(t_token	*token, t_cmd	*cmd, int version);
t_env	*add_exit_code_key_value(t_env	*env, t_cmd	*cmd);
int		decide_exit_code(t_cmd	*cmd, int ret);

#endif