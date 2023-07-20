/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:25:35 by snocita           #+#    #+#             */
/*   Updated: 2023/07/20 15:06:48 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_sig	g_sig;

char	**fill_this_little_tight_token(t_token *token, char **tab)
{
	int	i;

	i = 0;
	while (token && token->type < TRUNC)
	{
		tab[i] = ft_strdup(token->str);
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
	return (fill_this_little_tight_token(token, tab));
}

int	decide_exit_code(t_cmd	*cmd, int ret)
{
	if (ret == -1)
	{
		cmd->start = NULL;
		cmd->ret = CANNOTEXECUTE;
		return (CANNOTEXECUTE);
	}
	return (126);
}

int	run_cmd(char **args, t_env *env, t_cmd *cmd)
{
	char	*env_to_str;
	char	**env_array;
	pid_t	pid;

	if (cmd_validation(cmd) != 1)
	{
		printf("Minishelly: command %s not found\n", cmd->start->str);
		cmd->ret = COMMANDNOTFOUND;
		cmd->start = NULL;
		return (cmd->ret);
	}
	else
	{
		pid = fork();
		// signal_inprocess();
		if (pid == 0)
		{
			env_to_str = env_to_str_func(env);
			env_array = ft_split(env_to_str, '\n');
			ft_memdel(env_to_str);
			execve(cmd->start->path, args, env_array);
			exit(CANNOTEXECUTE);
		}
		else if (pid > 0)
			waitpid(pid, NULL, 0);
	}
	free(cmd->start->path);
	return (0);
}

void	program_exit(t_cmd *cmd, char **cmd_array)
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

//minishell
void	execution(t_cmd *cmd, t_token *token)
{
	char	**cmd_array;

	cmd_array = NULL;
	if (is_exact_match(cmd->start->str, "exit"))
	{
		pritnf("yo\n");
		program_exit(cmd);
		printf("yo!\n");
	}
	redirection_handler(token);
	if (is_builtin(cmd) == 1)
		return ;
	cmd_array = cmd_tab(token);
	if (cmd_array)
		cmd->ret = run_cmd(cmd_array, cmd->env, cmd);
	free_double_arr(cmd_array);
	return ;
}
