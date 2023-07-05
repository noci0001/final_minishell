/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:21:14 by snocita           #+#    #+#             */
/*   Updated: 2023/07/05 18:13:53 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_value_before_equal(char	*str)
{
	char	*value;
	size_t	i;

	i = 0;
	if (ft_strchr(str, '=') == NULL)
	{
		free(str);
		return (NULL);
	}
	while (str[i] && str[i] != '=')
		i++;
	value = malloc(sizeof(char) * (i + 1));
	if (!value)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] && str[i] != '=')
	{
		value[i] = str[i];
		i++;
	}
	free(str);
	value[i] = '\0';
	return (value);
}

int	is_inside_envp(t_env	*envp, t_cmd	*cmd)
{
	char	*to_export;
	char	*value;
	int		i;

	to_export = ft_strdup(cmd->start->next->str);
	to_export = get_value_before_equal(to_export);
	i = 0;

	while (envp->next != NULL)
	{
		value = envp->key_value[0];
		if (is_exact_match(value, to_export) == 1)
		{
			free(to_export);
			return (1);
		}
		envp = envp->next;
	}
	free(to_export);
	return (0);
}

int	ft_export(t_cmd	*cmd, t_env	*envp)
{
	t_env	*next_node;

	next_node = NULL;
	if (is_arg_absent(cmd, envp) == 1)
		return (1);
	if (is_inside_envp(envp, cmd) == 1)
	{
		while (is_exact_match(envp->key_value[0], get_value_before_equal(cmd->start->next->str)) != 1)
		{
			// printf("KEY VALUE: %s\n",envp->key_value[0]);
			// printf("STRING: %s\n",get_value_before_equal(cmd->start->next->str));
			// printf("CURR ENVP IS %s\n", envp->value);
			envp = envp->next;
		}
		// next_node = malloc(sizeof(t_env));
		// if (!next_node)
		// 	return (1);
		// next_node->value = ft_strdup(cmd->start->next->str);
		// next_node->prev = envp;
		// next_node->next = envp->next;
		// if (envp->next != NULL)
		// 	envp->next->prev = next_node;
		// envp->next = next_node;
		return (1);
	}
	else
	{
		while (envp->next != NULL)
			envp = envp->next;
		next_node = malloc(sizeof(t_env));
		if (!next_node)
			return (1);
		next_node->value = ft_strdup(cmd->start->next->str);
		next_node->prev = envp;
		next_node->next = NULL;
		envp->next = next_node;
	}
	return (1);
}
