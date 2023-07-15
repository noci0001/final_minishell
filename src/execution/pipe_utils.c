/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:16:11 by amurawsk          #+#    #+#             */
/*   Updated: 2023/07/11 00:34:16 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	do_pipes(t_cmd	*cmd, int	**fd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_pipes - 1)
	{
		if (pipe(fd[i]) < 0)
			exit(1);
		i++;
	}
}

void	close_fd(int **arrayfd, int pipes_number)
{
	int	i;

	i = 0;
	while (i < pipes_number)
	{
		close(arrayfd[i][0]);
		close(arrayfd[i][1]);
		i++;
	}
}

void	close_fd_childs(int **arrayfd, int pipes_number, int currentfd)
{
	int	i;

	i = 0;
	while (i < pipes_number)
	{
		if (i != currentfd)
			close(arrayfd[i][1]);
		if (currentfd - 1 != i)
			close(arrayfd[i][0]);
		i++;
	}
}

void	forking_function(char **args, t_cmd *cmd, int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		printf("Fork error");
	if (pid == 0)
	{
		close_fd_childs(cmd->fd, cmd->nb_pipes, i);
		if (i != cmd->nb_pipes)
			dup2(cmd->fd[i][1], STDOUT_FILENO);
		if (i != 0)
			dup2(cmd->fd[i - 1][0], STDIN_FILENO);
		redirection_handler(cmd->current_cmd);
		cmd->ret = run_cmd(args, cmd->env, cmd);
		close(cmd->fd[i][1]);
		if (i != 0)
			close(cmd->fd[i - 1][0]);
		exit(cmd->ret);
	}
}

void	wait_function(t_cmd *cmd)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i < cmd->nb_pipes)
	{
		wait(NULL);
		i++;
	}
	cmd->ret = WEXITSTATUS(exit_status);
}
