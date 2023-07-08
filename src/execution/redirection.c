/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:03:33 by snocita           #+#    #+#             */
/*   Updated: 2023/07/08 21:28:59 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void redirection_in(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY, 0777);
	if (fd == -1)
		return (ft_putstr_fd("Handling file failed\n", 2));
	dup2(fd, 0);
	ft_putstr_fd(str, fd);
	close(fd);
}

void redirection_out(char *str)
{
	int		fd;

	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return (ft_putstr_fd("Handling file failed\n", 2));
	dup2(fd, 1);
	close(fd);
}

void double_redirection(char *str)
{
	int		fd;
	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (ft_putstr_fd("Handling file failed\n", 2));
	dup2(fd, 1);
	close(fd);
}

void here_doc(char *str)
{
	int		fd;
	char	*line;

	fd = open(".secrectfile", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (ft_putstr_fd("Handling here_doc failed\n", 2));
	while (ft_strncmp(line, str, ft_strlen(line) != 0))
	{
		line = readline("<<" );
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	fd = open(".serectfile", O_RDONLY, 0777);
	dup2(fd,0);
	close(fd);
}

void	redirection_handler(t_token *token)
{
	while (token && token->next != NULL)
	{
		if (token->type == HEREDOC)
		{
			here_doc(token->next->str);
			printf("hello\n");
			return ;
		}
		else if (token->type == TRUNC)
			double_redirection(token->next->str);
		else if (token->type == APPEND)
			redirection_out(token->next->str);
		else if (token->type == INPUT)
			redirection_in(token->next->str);	
		token = token->next;
	}
}
