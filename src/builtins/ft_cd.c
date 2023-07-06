/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:43:04 by snocita           #+#    #+#             */
/*   Updated: 2023/07/06 17:29:24 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	update_pwd(t_env	*env)
{
	t_env	*node;
	char	cwdbuffer[1024];
	char	*cwd;

	while (env != NULL)
	{
		if (ft_strcmp(env->key_value[0], "PWD") == 0)
		{
			node = env;
			free(node->value);
			cwd = getcwd(cwdbuffer, sizeof(cwdbuffer));
			cwd = ft_strjoin("PWD=", cwd);
			node->value = ft_strdup(cwd);
			return (1);
		}
		env = env->next;
	}
	return (1);
}

int	navigate_backward(t_env	*env)
{
	char	cwdbuffer[1024];
	char	*cwd;
	size_t	cwd_len;
	char	*new_cwd;

	cwd = getcwd(cwdbuffer, sizeof(cwdbuffer));
	cwd_len = ft_strlen(cwd);

	while (cwd[cwd_len] != '/')
		cwd_len--;
	new_cwd = ft_substr(cwd, 0, cwd_len);
	if (chdir(new_cwd) == 0)
		update_pwd(env);
	return (1);
}

int	navigate_forward(t_env	*env, char	*arg)
{
	char	cwdbuffer[1024];
	char	*cwd;
	size_t	cwd_len;
	char	*new_cwd;
	char	*with_slash;
	char	*plus_fs;

	cwd = getcwd(cwdbuffer, sizeof(cwdbuffer));
	cwd_len = ft_strlen(cwd);
	with_slash = ft_strjoin("/", arg);
	new_cwd = ft_strjoin(cwd, with_slash);

	plus_fs = ft_strjoin(new_cwd, "/");
	if (chdir(new_cwd) == 0)
		update_pwd(env);
	else
		printf("");
	return (1);
}

int	navigate_home(t_env	*env)
{
	char	*home;

	home = ft_get_env(env, "HOME") + 5;
	if (chdir(home) == 0)
		update_pwd(env);
	return (1);
}

int	ft_cd(t_cmd	*cmd, t_env	*env)
{
	char	*arg;
	int		i;
	char	**splitted_path;
	
	if (is_arg_absent(cmd, env, 0) == 1)
	{
		navigate_home(env);
		return (1);
	}
	arg = ft_strdup(cmd->start->next->str);
	splitted_path = ft_split(arg, '/');
	i = 0;
	while (splitted_path[i] != NULL)
	{
		if (is_exact_match(splitted_path[i], "..") == 1)
			navigate_backward(env);
		else
			navigate_forward(env, splitted_path[i]);
		i++;
	}
	free_double_arr(splitted_path);
	free(arg);
	return (1);
}
