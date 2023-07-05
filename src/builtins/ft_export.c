/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:21:14 by snocita           #+#    #+#             */
/*   Updated: 2023/07/05 21:14:13 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char *get_value_before_equal(char *str)
{
	char *value;
	size_t i;

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

t_env *is_inside_envp(t_env *envp, t_cmd *cmd, int check)
{
	char *to_export;

	printf("PREVALUE _> %s\n", cmd->start->next->str);
	to_export = ft_strdup(cmd->start->next->str);
	printf("@VALUE TO EXPORT: %s\n", to_export);
	if (check == EXPORT)
	{
		to_export = get_value_before_equal(to_export);
		if (to_export == NULL)
			return (NULL);
	}
	printf("VALUE TO EXPORT: %s\n", to_export);
	while (envp->next != NULL)
	{
		printf("CHECKING: %s\n", envp->value);
		if (is_exact_match(envp->key_value[0], to_export) == 1)
		{
			printf("MATCH FOUND: %s\n", envp->value);
			free(to_export);
			return (envp);
		}
		if (envp->next != NULL)
			envp = envp->next;
	}
	printf("MATCH NOT FOUND\n");
	free(to_export);
	return (NULL);
}

int ft_export(t_cmd *cmd, t_env *envp)
{
	t_env *next_node;
	t_env *node_ptr;

	next_node = NULL;
	if (is_arg_absent(cmd, envp, EXPORT) == 1)
		return (1);
	node_ptr = is_inside_envp(envp, cmd, EXPORT);
	if (node_ptr != NULL)
	{
		free(node_ptr->value);
		node_ptr->value = ft_strdup(cmd->start->next->str);
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
	envp = cmd->env;
	return (1);
}

// int	ft_export(t_cmd	*cmd, t_env	*env)
// {
// 	//check arg if exist in lst
// 	//
// 	return (1);
// }