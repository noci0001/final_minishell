/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:25:35 by snocita           #+#    #+#             */
/*   Updated: 2023/07/09 13:26:12 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// converts token into double pointer
char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 1;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!(tab))
		return (NULL);
	token = start;
	i = 0;
	while (token && token->type < TRUNC)
	{
		tab[i] = token->str;
		if (!tab[i])
		{
			while (i > 0)
				free(tab[--i]);
			free(tab);
			return (NULL);
		}
		i++;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	run_cmd(char **args, t_env *env, t_cmd *cmd)
{
	char	*env_to_str;
	char	**env_array;
	pid_t	pid;

	if (cmd_validation(cmd) != 1)
	{
		printf("Minishelly: command %s not found\n", cmd->start->str);
		return (0);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			env_to_str = env_to_str_func(env);
			env_array = ft_split(env_to_str, '\n');
			ft_memdel(env_to_str);
			execve(cmd->start->path, args, env_array);
			exit(1);
			free_tab(env_array);
		}
		else if (pid > 0)
			waitpid(pid, NULL, 0);
	}
	return (0);
}

void	program_exit(t_cmd *cmd)
{
	cmd->exit = 1;
	free_token(cmd->start);
	exit(1);
}

void	execution(t_cmd *cmd, t_token *token)
{
	char	**cmd_array;
	int		i;

	if (is_exact_match(cmd->start->str, "exit"))
		program_exit(cmd);
	redirection_handler(token);
	if (is_builtin(cmd) == 1)
		return ;
	else
	{
		cmd_array = cmd_tab(token);
		i = 0;
		if (cmd_array)
			cmd->ret = run_cmd(cmd_array, cmd->env, cmd);
		else
			free_double_arr(cmd_array);
	}
	return ;
}
