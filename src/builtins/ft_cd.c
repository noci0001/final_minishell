/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:43:04 by snocita           #+#    #+#             */
/*   Updated: 2023/07/08 16:23:16 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	update_pwd(t_env	*env, char	*old_cwd)
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
			if (ft_strcmp(node->key_value[1], old_cwd) == 0)
			{
				printf("Values are IDENTICAL, KEEPING OLDPWD\n");
				return (1);
			}
		}
		if (ft_strcmp(env->key_value[0], "OLDPWD") == 0)
		{
			node = env;
			free(node->value);
			char *old_cwd2;
			old_cwd2 = ft_strjoin("OLDPWD=", old_cwd);
			node->value = ft_strdup(old_cwd2);
			return (1);
		}
		env = env->next;
	}
	return (1);
}

int	navigate_backward(t_env	*env, char	*curr_cwd)
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
		update_pwd(env, curr_cwd);
	return (1);
}

int	navigate_forward(t_env	*env, char	*arg, char	*curr_cwd)
{
	char	*cwd;
	size_t	cwd_len;
	char	*new_cwd;
	char	*with_slash;
	char	*plus_fs;

	cwd = ft_strdup(curr_cwd);
	cwd_len = ft_strlen(cwd);
	with_slash = ft_strjoin("/", arg);
	new_cwd = ft_strjoin(curr_cwd, with_slash);

	plus_fs = ft_strjoin(new_cwd, "/");
	printf("CURR CWD IS->%s\n", curr_cwd);
	if (chdir(new_cwd) == 0)
		update_pwd(env, curr_cwd);
	else
		printf("");
	return (1);
}

int	navigate_home(t_env	*env, char	*curr_cwd)
{
	char	*home;
	// char	*cwd;
	// char	cwdbuffer[1024];

	home = ft_get_env(env, "HOME") + 5;
	// get_cwd(t_env	*env);
	// cwd = getcwd(cwdbuffer, sizeof(cwdbuffer));
	if (chdir(home) == 0)
		update_pwd(env, curr_cwd);
	return (1);
}

int	ft_cd(t_cmd	*cmd, t_env	*env)
{
	char	*arg;
	int		i;
	char	**splitted_path;
	char	*cwd;
	char	cwdbuffer[1024];
	
	
	cwd = getcwd(cwdbuffer, sizeof(cwdbuffer));
	if (is_arg_absent(cmd, env, 0) == 1)
	{
		navigate_home(env, cwd);
		return (1);
	}
	arg = ft_strdup(cmd->start->next->str);
	if (arg[0] == '-' && arg[1] == '\0')
	{
		t_env	*oldpwd;
		ft_pwd(env);
		oldpwd = is_inside_envp(env, cmd, 0, "OLDPWD");
		// free(oldpwd->key_value[1]);
		// oldpwd->key_value[1] = ft_strdup(cwd);
		if (chdir(oldpwd->key_value[1]) == 0)
			update_pwd(env, cwd);
		else
			printf("NOPE\n");
		return (1);
	}
	splitted_path = ft_split(arg, '/');
	i = 0;
	while (splitted_path[i] != NULL)
	{
		if (is_exact_match(splitted_path[i], "..") == 1)
			navigate_backward(env, cwd);
		else
			navigate_forward(env, splitted_path[i], cwd);
		i++;
	}
	free_double_arr(splitted_path);
	free(arg);
	return (1);
}
