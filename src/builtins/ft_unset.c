/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:01:07 by snocita           #+#    #+#             */
/*   Updated: 2023/07/09 15:44:44 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	absent_or_not(t_cmd	*cmd, t_env	*env)
{
	char	*value_before_equal;

	if (is_arg_absent(cmd, env, UNSET) == 1)
	{
		ft_putendl_fd("unset: wrong unsettable argument", 1);
		return (1);
	}
	else
	{
		value_before_equal = ft_strdup(cmd->start->next->str);
		value_before_equal = get_value_before_equal(value_before_equal);
		if (value_before_equal != NULL)
		{
			free(value_before_equal);
			return (1);
		}
	}
	return (1);
}

int	ft_unset(t_cmd *cmd, t_env *env)
{
	t_env	*node_ptr;

	absent_or_not(cmd, env);
	node_ptr = is_inside_envp(env, cmd, UNSET, NULL);
	if (node_ptr != NULL)
	{
		node_ptr->prev->next = node_ptr->next;
		if (node_ptr->next != NULL)
			node_ptr->next->prev = node_ptr->prev;
	}
	return (1);
}
