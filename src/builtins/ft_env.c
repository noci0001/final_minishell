/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:21:22 by snocita           #+#    #+#             */
/*   Updated: 2023/07/06 11:56:14 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void add_key_value(t_env	*env)
{
	char	**key_value_array;

	key_value_array = ft_split(env->value, '=');
	env->key_value[0] = ft_strdup(key_value_array[0]);
	env->key_value[1] = ft_strdup(key_value_array[1]);
	free_double_arr(key_value_array);

	return ;
}

int	obtain_envp(t_cmd *cmd, char **envp)
{
	t_env	*env;
	t_env	*new;
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
		add_key_value(new);
		// printf("KEY: %s\tVALUE: %s\n", new->key_value[0], new->key_value[1]);
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
