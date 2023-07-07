/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:01:07 by snocita           #+#    #+#             */
/*   Updated: 2023/07/07 14:34:00 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_unset(t_cmd *cmd, t_env *env)
{
	char	*value_before_equal;
	t_env	*node_ptr;

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
	node_ptr = is_inside_envp(env, cmd, UNSET, NULL);
	if (node_ptr != NULL)
	{
		node_ptr->prev->next = node_ptr->next;
		if (node_ptr->next != NULL)
			node_ptr->next->prev = node_ptr->prev;
		// free_double_arr(node_ptr->key_value);
		// free(node_ptr->value);
		// free(node_ptr);
	}
	return (1);
}
