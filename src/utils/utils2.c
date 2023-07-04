/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:21:03 by snocita           #+#    #+#             */
/*   Updated: 2023/07/04 17:21:14 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_arg_absent(t_cmd	*cmd, t_env	*envp)
{
	if (cmd->start->next == NULL && envp)
	{
		ft_env(envp);
		return (1);
	}
	return (0);
}
