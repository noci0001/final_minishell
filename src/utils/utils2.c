/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:21:03 by snocita           #+#    #+#             */
/*   Updated: 2023/07/05 19:58:39 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_arg_absent(t_cmd	*cmd, t_env	*envp, int check)
{
	if ((cmd->start->next == NULL) && envp && (check == UNSET))
		return (1);
	if ((cmd->start->next == NULL) && envp)
	{
		ft_env(envp);
		return (1);
	}
	return (0);
}
