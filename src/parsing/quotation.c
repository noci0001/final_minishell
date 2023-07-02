/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:50:33 by snocita           #+#    #+#             */
/*   Updated: 2023/07/02 17:37:20 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//if the token is null, CMD or ARG
// and there is no previus sep token,
//  or there 
int	is_last_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || is_type(token, CMD) || is_type(token, ARG))
	{
		prev = prev_sep(token, NOSKIP);
		if (!prev || is_type(prev, END) || is_type(prev, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

int	is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;", line[i]))
		return (0);
	else if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (1);
	else
		return (0);
}

char	*space_alloc(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	new = malloc(sizeof(char) * (i + 2 * count + 1));
	if (!new)
		return (NULL);
	return (new);
}

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	// ft_memdel(line);
	return (new);
}

//If open is 0, it means there are no open quotes.
//If open is 1, there is an open double quote.
//If open is 2 instead, it means there is an open single quote.
int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

//PROBLEM FREEING LINE
//a.out(9369,0x2046a2e00) malloc: *** error for object 0x30ca566f0: pointer being freed was not allocated
//a.out(9369,0x2046a2e00) malloc: *** set a breakpoint in malloc_error_break to debug
//[1]    9369 abort
// check for open quotes
int	quote_check(t_cmd *cmd, char **line)
{
	if (quotes(*line, 2147483647))
	{
		printf("\033[0;32mMinishelly$\033[0m: syntax error with open quotes\n");
		if (line != NULL)
		{
			free_double_arr(line);
			printf("line freed!\n");
		}
		ft_memdel(*line);
		cmd->ret = 2;
		cmd->start = NULL;
		return (1);
	}
	return (0);
}

//takes input received through readline
// and the struct. 
void	parse(char	*line, t_cmd *cmd)
{
	t_token	*token;

	// debug_get_full_input(line);
	if (quote_check(cmd, &line))
		return ;
	line = space_line(line);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	cmd->start = get_tokens(line);
	ft_memdel(line);
	squish_args(cmd);
	token = cmd->start;
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		// debug_token_interception(token->str, token->type);
		token = token->next;
	}
}
