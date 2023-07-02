/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:25:35 by snocita           #+#    #+#             */
/*   Updated: 2023/07/02 17:32:02 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//converts token into double pointer
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
	if (!(tab))
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

int	is_builtin(t_cmd	*cmd)
{
	printf("checking if builtin!\n");
	// if (ft_strcmp(cmd.start->str, "cd") == 0)
	// 	return (ft_cd(cmd.start));
	if (ft_strcmp(cmd->start->str, "echo") == 0)
		return (ft_echo(cmd->start));
	if (ft_strcmp(cmd->start->str, "pwd") == 0)
		return (ft_pwd(cmd->env));
	if (ft_strcmp(cmd->start->str, "export") == 0)
		// return (ft_export(cmd->start));
		printf("ADD EXPORT FUNCTION\n");
	if (ft_strcmp(cmd->start->str, "env") == 0)
		return (ft_env(cmd->env));
	if (ft_strcmp(cmd->start->str, "exit") == 0)
	{
		cmd->exit = 1;
		return (1);
	}
	else
		printf("NOT A BUILTIN!\n");
	return (0);
}

int	run_cmd(char **args, t_env *env, t_cmd	*cmd)
{
	char	*env_to_str;
	char	**env_array;
	pid_t	pid;

	if (cmd_validation(cmd) != 1)
	{
		program_exit(cmd);
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
			// free_tab(env_array);
			// free_token(cmd->start);
		}
		else
			waitpid(pid, 0, 0);
	}
	return (0);
}

void	program_exit(t_cmd	*cmd)
{
	cmd->exit = 1;
	free_token(cmd->start);
	free_env(cmd->env);
	free(cmd->input);
	exit(1);
}

void	execution(t_cmd	*cmd, t_token	*token)
{
	char	**cmd_array;
	int		i;

	cmd_array = cmd_tab(token);
	printf("printing array...\n");
	print_double_array(cmd_array);
	printf("\n");
	i = 0;
	while (cmd_array && cmd_array[i])
	{
		//HERE IS WHERE EXPANSION HAPPEN
		printf("checking for expansion...\n");
		i++;
	}
	if (cmd_array && ft_strcmp(cmd_array[0], "exit") == 0)
		program_exit(cmd);
	else if (cmd_array && (is_builtin(cmd) != 1))
		cmd->ret = run_cmd(cmd_array, cmd->env, cmd);
	// free_double_arr(cmd_array);
}
// && (is_builtin(cmd) != 1)


// int			magic_box(char *path, char **args, t_env *env, t_mini *mini)
// {
// 	char	**env_array;
// 	char	*ptr;
// 	int		ret;

// 	ret = SUCCESS;
// 	g_sig.pid = fork();
// 	if (g_sig.pid == 0)
// 	{
// 		ptr = env_to_str(env);
// 		env_array = ft_split(ptr, '\n');
// 		ft_memdel(ptr);
// 		if (ft_strchr(path, '/') != NULL)
// 			execve(path, args, env_array);
// 		ret = error_message(path);
// 		free_tab(env_array);
// 		free_token(mini->start);
// 		exit(ret);
// 	}
// 	else
// 		waitpid(g_sig.pid, &ret, 0);
// 	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
// 		return (g_sig.exit_status);
// 	ret = (ret == 32256 || ret == 32512) ? ret / 256 : !!ret;
// 	return (ret);
// }