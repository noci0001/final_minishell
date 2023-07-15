/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:51:30 by snocita           #+#    #+#             */
/*   Updated: 2023/07/10 23:34:09 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

// traverses the list backwards
// until it returns the previous separator token
t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD)
			token = token->next;
	}
	return (token);
}

int	how_many_pipes(t_token *start)
{
	int	i;

	i = 0;
	while (start)
	{
		if (start->type == CMD)
			i++;
		start = start->next;
	}
	return (i);
}

void	malloc_fds(t_cmd *cmd)
{
	int		i;

	cmd->fd = malloc(sizeof(int *) * cmd->nb_pipes);
	i = 0;
	while (i < cmd->nb_pipes)
	{
		cmd->fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
}