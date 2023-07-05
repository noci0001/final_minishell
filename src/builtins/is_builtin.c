/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:51:59 by snocita           #+#    #+#             */
/*   Updated: 2023/07/05 18:16:30 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_builtin(t_cmd	*cmd)
{
	// if (is_exact_match(cmd->start->str, "cd") == 0)
	// 	return (ft_cd(cmd, cmd->env));
	if (is_exact_match(cmd->start->str, "echo"))
		return (ft_echo(cmd->start));
	else if (is_exact_match(cmd->start->str, "pwd"))
		return (ft_pwd(cmd->env));
	else if (is_exact_match(cmd->start->str, "export"))
		return (ft_export(cmd, cmd->env));
	else if (is_exact_match(cmd->start->str, "unset"))
		return (ft_unset(cmd, cmd->env));
	else if (is_exact_match(cmd->start->str, "env"))
		return (ft_env(cmd->env));
	else if (is_exact_match(cmd->start->str, "exit"))
	{
		return (-1);
	}
	else
		return (0);
}