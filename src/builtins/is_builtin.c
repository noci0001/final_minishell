/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:51:59 by snocita           #+#    #+#             */
/*   Updated: 2023/07/09 15:40:18 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_builtin(t_cmd	*cmd)
{
	if (is_exact_match(cmd->start->str, "cd"))
		return (ft_cd(cmd, cmd->env));
	if (is_exact_match(cmd->start->str, "echo"))
		return (ft_echo(cmd->start, cmd, cmd->env));
	else if (is_exact_match(cmd->start->str, "pwd"))
		return (ft_pwd(cmd->env));
	else if (is_exact_match(cmd->start->str, "export"))
		return (ft_export(cmd, cmd->env));
	else if (is_exact_match(cmd->start->str, "unset"))
		return (ft_unset(cmd, cmd->env));
	else if (is_exact_match(cmd->start->str, "env"))
		return (ft_env(cmd->env));
	else
		return (0);
}
