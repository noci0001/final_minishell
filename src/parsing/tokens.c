/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:40:40 by snocita           #+#    #+#             */
/*   Updated: 2023/07/08 21:02:22 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//skips anything that is a 
//" ", "\t", "\r", "\v" or '\f'
void	ft_skip_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

int		ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
				&& line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

//allocate space for the interception of
// the next token
int		next_alloc(char *line, int *i)
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

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;
	int		disable_exp;

	j = 0;
	c = ' ';
	disable_exp = 0;
	if (!(token = malloc(sizeof(t_token)))
	|| !(token->str = malloc(sizeof(char) * next_alloc(line, i))))
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
		{
			if ((ft_strchr(line, '$') != NULL && line[*i] == '\''))
				token->exp_disabled = 1;	
			c = line[(*i)++];
		}
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			token->str[j++] = line[(*i)++];
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}


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
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			token->next = (prev) ? prev->next : cmd->start;
			prev = (prev) ? prev : token;
			prev->next->prev = token;
			prev->next = (cmd->start->prev) ? prev->next : token;
			cmd->start = (cmd->start->prev) ? cmd->start->prev : cmd->start;
		}
		token = token->next;
	}
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
	else if (token->prev == NULL || token->prev->type >= TRUNC )
		token->type = CMD;
	else
		token->type = ARG;
	// if (token->str[0] == '-' && token->prev->type == CMD)
	// 	token->type = FLAG;
}

t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;
	int		squote;

	squote = 1;
	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		// if (line[i] == '\'')
		// 	squote *= -1;
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &i);
	}
	// if (squote == 1)
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}