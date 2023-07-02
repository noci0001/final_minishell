/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:21:22 by snocita           #+#    #+#             */
/*   Updated: 2023/07/02 17:10:32 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	obtain_envp(t_cmd	*cmd, char **envp)
{
	t_env	*new;
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(envp[0]);
	env->next = NULL;
	cmd->env = env;
	i = 1;
	while (envp && envp[0] && envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(envp[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

char	*env_to_str_func(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	if (!(env = malloc(sizeof(char) * size_env(lst) + 1)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
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
	return (0);
}
