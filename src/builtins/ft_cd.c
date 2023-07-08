/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:43:04 by snocita           #+#    #+#             */
/*   Updated: 2023/07/08 19:14:55 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	update_oldpwd(t_env		*env, char	*old_cwd)
{
	char	*old_cwd2;
	t_env	*node;

	while (env != NULL)
	{
		if (ft_strcmp(env->key_value[0], "OLDPWD") == 0)
		{
			node = env;
			free(node->value);
			old_cwd2 = ft_strjoin("OLDPWD=", old_cwd);
			node->value = ft_strdup(old_cwd2);
			return ;
		}
		env = env->next;
	}
}

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

	cwd = getcwd(cwdbuffer, sizeof(cwdbuffer));
	cwd_len = ft_strlen(cwd);
	with_slash = ft_strjoin("/", arg);
	new_cwd = ft_strjoin(cwd, with_slash);
	if (chdir(new_cwd) == 0)
		update_pwd(env);
	else
		printf("");
	return (1);
}

int	navigate_home(t_env	*env, int is_tilde, t_cmd	*cmd)
{
	char	*home;

	home = ft_get_env(env, "HOME") + 5;
	if (chdir(home) == 0)
		update_pwd(env);
	if (is_tilde == 1 && cmd->start->next->str[2])
		go_places(cmd->start->next->str + 2, env);
	return (1);
}

int	go_places(char	*arg, t_env	*env)
{
	int		i;
	char	**splitted_path;

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
	return (1);
}

int	ft_cd(t_cmd	*cmd, t_env	*env)
{
	char	*arg;
	char	*cwd;
	t_env	*oldpwd;
	char	cwdbuffer[1024];
	
	cwd = getcwd(cwdbuffer, sizeof(cwdbuffer));
	update_pwd(env);
	update_oldpwd(env, cwd);
	if (is_arg_absent(cmd, env, 0) == 1)
		return (navigate_home(env, 0, NULL));
	if (cmd->start->next->str[0] == '~')
		return (navigate_home(env, 1, cmd));
	arg = ft_strdup(cmd->start->next->str);
	if (arg[0] == '-' && arg[1] == '\0')
	{
		oldpwd = is_inside_envp(env, cmd, 0, "OLDPWD");
		chdir(oldpwd->key_value[1]);
		return (update_pwd(env));
	}
	go_places(arg, env);
	free(arg);
	return (1);
}
