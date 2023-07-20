/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:04:37 by snocita           #+#    #+#             */
/*   Updated: 2023/07/20 15:09:25 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//minishell
void	execution(t_cmd *cmd)
{
	t_token	*token;
	int		status;

	token = next_run(cmd->start, NOSKIP);
	if (is_types(cmd->start, "TAI") != 0)
		token = cmd->start->next;
	while (cmd->exit == 0 && token)
	{
		cmd->responsibility = 1;
		cmd->parent = 1;
		cmd->last = 1;
		redir_and_exec(cmd, token);
		reset_std(cmd);
		close_fds(cmd);
		reset_fds(cmd);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (cmd->last == 0)
			cmd->ret = status;
		if (cmd->parent == 0)
		{
			free_token(cmd->start);
			exit(cmd->ret);
		}
		cmd->no_exec = 0;
		token = next_run(token, SKIP);
	}
}

void	run_cmd(t_cmd *cmd, t_token *token)
{
	char	**cmd_array;

	if (cmd->responsibility == 0)
		return ;
	cmd_array = cmd_tab(token);
	if (cmd_array && ft_strcmp(cmd_array[0], "exit") == 0 
		&& has_pipe(token) == 0)
	{
		printf("before!\n");
		program_exit(cmd, cmd_array);
		printf("yo!\n");
	}
	else if (cmd_array && is_builtin(cmd))
	{
		do_builtin(cmd);
		cmd->ret = 0;
	}
	else if (cmd_array)
		cmd->ret = exec_cmd(cmd_array, cmd->env, cmd);
	// free_tab(cmd_array);
	ft_close(cmd->pipin);
	ft_close(cmd->pipout);
	cmd->pipin = -1;
	cmd->pipout = -1;
	cmd->responsibility = 0;
}

void	program_exit(t_cmd *cmd, char	**cmd_array)
{
	cmd->exit = 1;
	ft_putstr_fd("exit ", STDERR_FILENO);
	// cmd_array[1] ? ft_putendl_fd("❤️", STDERR_FILENO) : ft_putendl_fd("💚", STDERR_FILENO);
	if (cmd_array[1] && cmd_array[2])
	{
		cmd->ret = 1;
		ft_putendl_fd("Minishelly: exit: too many arguments", STDERR_FILENO);
	}
	else if (cmd_array[1] && ft_strisnum(cmd_array[1]) == 0)
	{
		cmd->ret = 255;
		ft_putstr_fd("Minishelly: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd_array[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	else if (cmd_array[1])
		cmd->ret = ft_atoi(cmd_array[1]);
	else
		cmd->ret = 0;
}

// converts token into double pointer
char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	redir_and_exec(t_cmd *cmd, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(cmd, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(cmd, token, APPEND);
	else if (is_type(prev, INPUT))
		input(cmd, token);
	else if (is_type(prev, PIPE))
		pipe = cmdpipe(cmd);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(cmd, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && cmd->no_exec == 0)
		run_cmd(cmd, token);
}
