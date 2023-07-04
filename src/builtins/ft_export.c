/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:21:14 by snocita           #+#    #+#             */
/*   Updated: 2023/07/04 17:46:01 by snocita          ###   ########.fr       */
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
		return (NULL);
	}
	while (str[i] && str[i] != '=')
		i++;
	value = malloc(sizeof(char) * (i + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		value[i] = str[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

int	is_inside_envp(t_env	*envp, t_cmd	*cmd)
{
	char	*to_export;
	char	*value;
	int		i;

	to_export = ft_strdup(cmd->start->next->str);
	i = 0;

	while (envp->next != NULL)
	{
		value = envp->key_value[0];
		if (is_exact_match(value, to_export) == 1)
			return (1);
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
		next_node = malloc(sizeof(t_env));
		if (!next_node)
			return (1);
		next_node->value = ft_strdup(cmd->start->next->str);
		next_node->prev = envp;
		next_node->next = envp->next;
		if (envp->next != NULL)
			envp->next->prev = next_node;
		envp->next = next_node;
		return (1);
	}
	next_node->value = ft_strdup(cmd->start->next->str);
	next_node->prev = envp;
	next_node->next = NULL;
	envp->next = next_node;
	return (1);
}
