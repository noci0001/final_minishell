/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:21:14 by snocita           #+#    #+#             */
/*   Updated: 2023/07/05 18:32:31 by snocita          ###   ########.fr       */
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

t_env	*is_inside_envp(t_env	*envp, t_cmd	*cmd)
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
			return (envp);
		}
		envp = envp->next;
	}
	free(to_export);
	return (NULL);
}

int	ft_export(t_cmd	*cmd, t_env	*envp)
{
	t_env	*next_node;
	t_env	*node_ptr;

	next_node = NULL;
	if (is_arg_absent(cmd, envp) == 1)
		return (1);
	node_ptr = is_inside_envp(envp, cmd);
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
	return (1);
}
