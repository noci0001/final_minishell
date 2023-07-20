/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:03:33 by snocita           #+#    #+#             */
/*   Updated: 2023/07/20 14:38:58 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void	redirection_in(char *str)
// {
// 	int	fd;

// 	fd = open(str, O_RDONLY, 0777);
// 	if (fd == -1)
// 		return (ft_putstr_fd("Handling file failed\n", 2));
// 	dup2(fd, 0);
// 	ft_putstr_fd(str, fd);
// 	close(fd);
// }

// void	redirection_out(char *str)
// {
// 	int		fd;

// 	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	if (fd == -1)
// 		return (ft_putstr_fd("Handling file failed\n", 2));
// 	dup2(fd, 1);
// 	close(fd);
// }

// void	double_redirection(char *str)
// {
// 	int		fd;

// 	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (fd == -1)
// 		return (ft_putstr_fd("Handling file failed\n", 2));
// 	dup2(fd, 1);
// 	close(fd);
// }

// void	here_doc(char *str)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open(".secrectfile", O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (fd == -1)
// 		return (ft_putstr_fd("Handling here_doc failed\n", 2));
// 	while (ft_strncmp(line, str, ft_strlen(line) != 0))
// 	{
// 		line = readline("<<" );
// 		ft_putstr_fd(line, fd);
// 		ft_putstr_fd("\n", fd);
// 		free(line);
// 	}
// 	close(fd);
// 	fd = open(".serectfile", O_RDONLY, 0777);
// 	dup2(fd, 0);
// 	close(fd);
// }

// void	redirection_handler(t_token *token)
// {
// 	while (token && token->next != NULL)
// 	{
// 		if (token->type == HEREDOC)
// 		{
// 			here_doc(token->next->str);
// 			printf("hello\n");
// 			return ;
// 		}
// 		else if (token->type == TRUNC)
// 			double_redirection(token->next->str);
// 		else if (token->type == APPEND)
// 			redirection_out(token->next->str);
// 		else if (token->type == INPUT)
// 			redirection_in(token->next->str);
// 		token = token->next;
// 	}
// }

void	redir(t_cmd *cmd, t_token *token, int type)
{
	ft_close(cmd->fdout);
	if (type == TRUNC)
		cmd->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		cmd->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (cmd->fdout == -1)
	{
		ft_putstr_fd("cmdshell: ", STDERR_FILENO);
		ft_putstr_fd(token->str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		cmd->ret = 1;
		cmd->no_exec = 1;
		return ;
	}
	dup2(cmd->fdout, STDOUT_FILENO);
}

void	input(t_cmd *cmd, t_token *token)
{
	ft_close(cmd->fdin);
	cmd->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (cmd->fdin == -1)
	{
		ft_putstr_fd("Minishelly: ", STDERR_FILENO);
		ft_putstr_fd(token->str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		cmd->ret = 1;
		cmd->no_exec = 1;
		return ;
	}
	dup2(cmd->fdin, STDIN_FILENO);
}

int	cmdpipe(t_cmd *cmd)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		cmd->pipin = pipefd[0];
		cmd->pid = -1;
		cmd->parent = 0;
		cmd->no_exec = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		cmd->pipout = pipefd[1];
		cmd->pid = pid;
		cmd->last = 0;
		return (1);
	}
}
