/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:19:38 by snocita           #+#    #+#             */
/*   Updated: 2023/07/20 14:22:56 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_cmd *cmd)
{
	dup2(cmd->in, STDIN_FILENO);
	dup2(cmd->out, STDOUT_FILENO);
}

void	close_fds(t_cmd *cmd)
{
	ft_close(cmd->fdin);
	ft_close(cmd->fdout);
	ft_close(cmd->pipin);
	ft_close(cmd->pipout);
}

void	reset_fds(t_cmd *cmd)
{
	cmd->fdin = -1;
	cmd->fdout = -1;
	cmd->pipin = -1;
	cmd->pipout = -1;
	cmd->pid = -1;
}
