/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:40:40 by snocita           #+#    #+#             */
/*   Updated: 2023/07/09 14:58:52 by snocita          ###   ########.fr       */
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

int	ignore_sep(char *line, int i)
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

t_token	*next_token2(char *line, int *i, char c, t_token	*token)
{
	int	j;

	j = 0;
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

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	char	c;

	c = ' ';
	token = malloc(sizeof(t_token));
	token->str = malloc(sizeof(char) * next_alloc(line, i));
	if (!token || !(token->str))
		return (NULL);
	return (next_token2(line, i, c, token));
}

t_token	*get_tokens(char *line)
{
	int		i;
	int		squote;

	squote = 1;
	i = 0;
	ft_skip_space(line, &i);
	return (loop_through_line(line, i));
}
