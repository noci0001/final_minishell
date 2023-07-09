/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:21:03 by snocita           #+#    #+#             */
/*   Updated: 2023/07/09 15:03:11 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*loop_through_line(char *line, int index)
{
	t_token	*prev;
	t_token	*next;
	int		sep;

	prev = NULL;
	next = NULL;
	while (line[index])
	{
		sep = ignore_sep(line, index);
		next = next_token(line, &index);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &index);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

//through strcmp this function determines
// which type of arg it is
//possibilities are: "> >> < | ;"
void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "<<") == 0 && separator == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

void	squish_args2(t_cmd *cmd, t_token *token, t_token	*prev)
{
	token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	token->prev = prev;
	if (prev != NULL)
		token->next = prev->next;
	else
		token->next = cmd->start;
	if (prev == NULL)
		prev = token;
	prev->next->prev = token;
	if (cmd->start->prev != NULL)
		prev->next = prev->next;
	else
		prev->next = token;
	if (cmd->start->prev != NULL)
		cmd->start = cmd->start->prev;
	else
		cmd->start = cmd->start;
}

// token->next = (prev) ? prev->next : cmd->start;
// prev = (prev) ? prev : token;
// prev->next->prev = token;
// prev->next = (cmd->start->prev) ? prev->next : token;
// cmd->start = (cmd->start->prev) ? cmd->start->prev : cmd->start;
void	squish_args(t_cmd *cmd)
{
	t_token	*token;
	t_token	*prev;

	token = cmd->start;
	while (token)
	{
		prev = prev_sep(token, NOSKIP);
		if (is_type(token, ARG) && is_types(prev, "TAI"))
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			squish_args2(cmd, token, prev);
		}
		token = token->next;
	}
}

//allocate space for the interception of
// the next token
int	next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}
