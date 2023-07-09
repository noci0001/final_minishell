/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:01:33 by snocita           #+#    #+#             */
/*   Updated: 2023/07/09 13:06:55 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	update_oldpwd(t_env	*env, char	*old_cwd)
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
