/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:21:22 by snocita           #+#    #+#             */
/*   Updated: 2023/07/04 17:15:08 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// int	obtain_envp(t_cmd	*cmd, char **envp)
// {
// 	t_env	*new;
// 	t_env	*env;
// 	char	**key_value_array;
// 	int		i;

// 	env = NULL;
// 	env = malloc(sizeof(t_env));
// 	if (!env && !env->head)
// 		return (1);
// 	env->value = ft_strdup(envp[0]);
// 	key_value_array = ft_split(envp[0], '=');
// 	env->key_value[0] = ft_strdup(key_value_array[0]);
// 	env->key_value[1] = ft_strdup(key_value_array[1]);
// 	free_double_arr(key_value_array);
// 	env->next = NULL;
// 	cmd->env = env;
// 	i = 1;
// 	while (envp && envp[0] && envp[i])
// 	{
// 		new = malloc(sizeof(t_env));
// 		if (!new)
// 			return (1);
// 		new->value = ft_strdup(envp[i]);
// 		key_value_array = ft_split(envp[i], '=');
// 		env->key_value[0] = ft_strdup(key_value_array[0]);
// 		env->key_value[1] = ft_strdup(key_value_array[1]);
// 		free_double_arr(key_value_array);
// 		new->next = NULL;
// 		new->prev = env;
// 		env->next = new;
// 		env = new;
// 		i++;
// 	}
// 	return (0);
// }

int	obtain_envp(t_cmd *cmd, char **envp)
{
	t_env	*env;
	t_env	*new;
	char	**key_value_array;
	int		i;

	i = 0;
	env = NULL;
	while (envp && envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
		{
			free_env_list(cmd->env);
			return (1);
		}
		new->value = ft_strdup(envp[i]);
		key_value_array = ft_split(envp[i], '=');
		new->key_value[0] = key_value_array[0];
		new->key_value[1] = key_value_array[1];
		free_double_arr(key_value_array);
		new->prev = env;
		if (env)
			env->next = new;
		else
			cmd->env = new;
		env = new;
		i++;
	}
	if (env)
		env->next = NULL;
	return (0);
}

char	*env_to_str_func(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = malloc(sizeof(char) * size_env(lst) + 1);
	if (!(env))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i++] = lst->value[j++];
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 1);
	return (1);
}
