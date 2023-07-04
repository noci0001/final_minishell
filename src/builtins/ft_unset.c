/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:01:07 by snocita           #+#    #+#             */
/*   Updated: 2023/07/04 17:07:37 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_unset(t_cmd *cmd, t_env *env)
{
	char	*to_unset;

	if (cmd->start->next != NULL)
		to_unset = cmd->start->next->str;
	else
	{
		ft_putendl_fd("unset: not enough arguments", 1);
		return (1);
	}
	while (env->next != NULL)
	{
		if (get_value_before_equal(to_unset) != NULL)
			return (0);
		if (is_exact_match(env->key_value[0], to_unset) == 1)
			env->prev->next = env->next;
		env = env->next;
	}
	if (is_exact_match(get_value_before_equal(env->value), to_unset) == 1)
		env->prev->next = env->next;
	return (1);
}
