/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:21:14 by snocita           #+#    #+#             */
/*   Updated: 2023/07/09 15:29:47 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_value_from_before_equal(char	*str, int index)
{
	char	*value;

	value = malloc(sizeof(char) * (index + 1));
	if (!value)
	{
		free(str);
		return (NULL);
	}
	index = 0;
	while (str[index] && str[index] != '=')
	{
		value[index] = str[index];
		index++;
	}
	free(str);
	value[index] = '\0';
	return (value);
}

char	*get_value_before_equal(char *str)
{
	size_t	i;

	i = 0;
	if (ft_strchr(str, '=') == NULL)
	{
		free(str);
		return (NULL);
	}
	while (str[i] && str[i] != '=')
		i++;
	return (get_value_from_before_equal(str, i));
}

t_env	*is_inside_envp(t_env *envp, t_cmd *cmd, int check, char	*str)
{
	char	*to_export;

	if (str != NULL)
		to_export = ft_strdup(str);
	else
		to_export = ft_strdup(cmd->start->next->str);
	if (check == EXPORT)
	{
		to_export = get_value_before_equal(to_export);
		if (to_export == NULL)
			return (NULL);
	}
	while (envp != NULL)
	{
		if (is_exact_match(envp->key_value[0], to_export) == 1)
		{
			free(to_export);
			return (envp);
		}
		envp = envp->next;
	}
	free(to_export);
	return (NULL);
}

int	add_node_to_envp(t_env *envp, t_cmd	*cmd)
{
	t_env	*last_node;
	t_env	*next_node;

	next_node = NULL;
	last_node = envp;
	while (last_node->next != NULL)
		last_node = last_node->next;
	next_node = malloc(sizeof(t_env));
	if (!next_node)
		return (1);
	next_node->value = ft_strdup(cmd->start->next->str);
	add_key_value(next_node);
	next_node->prev = last_node;
	next_node->next = NULL;
	last_node->next = next_node;
	envp = next_node;
	return (1);
}

int	ft_export(t_cmd *cmd, t_env *envp)
{
	t_env	*node_ptr;

	if (is_arg_absent(cmd, envp, EXPORT) == 1)
		return (1);
	node_ptr = is_inside_envp(envp, cmd, EXPORT, NULL);
	if (node_ptr != NULL)
	{
		free(node_ptr->value);
		node_ptr->value = ft_strdup(cmd->start->next->str);
		return (1);
	}
	else
		add_node_to_envp(envp, cmd);
	return (1);
}
