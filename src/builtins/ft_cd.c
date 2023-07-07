/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:43:04 by snocita           #+#    #+#             */
/*   Updated: 2023/07/07 20:36:12 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	update_pwd(t_env	*env, char	*cwd)
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
		else if (ft_strcmp(env->key_value[0], "OLDPWD") == 0)
		{
			node = env;
			free(node->value);
			cwd = ft_strjoin("OLDPWD=", cwd);
			node->value = ft_strdup(cwd);
			printf("PREVIOUS -> %s\n", node->value);
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
		update_pwd(env, cwd);
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
		update_pwd(env, cwd);
	else
		printf("");
	return (1);
}

int	navigate_home(t_env	*env)
{
	char	*home;
	char	*cwd;
	char	cwdbuffer[1024];

	home = ft_get_env(env, "HOME") + 5;
	cwd = getcwd(cwdbuffer, sizeof(cwdbuffer));
	if (chdir(home) == 0)
		update_pwd(env, cwd);
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
	if (arg[0] == '-' && arg[1] == '\0')
	{
		t_env	*oldpwd;
		printf("Yo mama?\n");
		oldpwd = is_inside_envp(env, cmd, 0, "OLDPWD");
		free(oldpwd->key_value[1]);
		oldpwd->key_value[1] = "YOMAMA\n";
		update_pwd(env, );
		return (1);
	}
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
