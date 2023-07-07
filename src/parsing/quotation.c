/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:50:33 by snocita           #+#    #+#             */
/*   Updated: 2023/07/07 19:17:47 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// if the token is null, CMD or ARG
//  and there is no previus sep token,
//   or there
int is_last_valid_arg(t_token *token)
{
	t_token *prev;

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

char *space_alloc(char *line)
{
	char *new;
	int count;
	int i;

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

char *space_line(char *line)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new &&line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
		{
			new[j++] = line[i++];
			// TEMP
			//  char word_to_expand[50];
			//  int k = 0;
			//  while (new[k] != ' ' && new[k])
			//  {
			//  	word_to_expand[k] = new[k];
			//  	k++;
			//  }
			//  word_to_expand[k] = '\0';
			//  printf("WORD IS -> %s\n", word_to_expand);
			// END TEMP
		}
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
	ft_memdel(line);
	return (new);
}

// check for open quotes
int quote_check(t_cmd *cmd, char **line)
{
	if (quotes(*line, 2147483647))
	{
		printf("\033[0;32mMinishelly$\033[0m: syntax error with open quotes\n");
		ft_memdel(*line);
		cmd->ret = 2;
		cmd->start = NULL;
		return (1);
	}
	return (0);
}

// takes input received through readline
//  and the struct.
void parse(char *line, t_cmd *cmd)
{
	t_token *token;

	if (quote_check(cmd, &line))
		return;
	line = space_line(line);
	cmd->start = get_tokens(line);
	ft_memdel(line);
	squish_args(cmd);
	token = cmd->start;
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		check_expansion(cmd, token);
		token = token->next;
	}
}

void check_expansion(t_cmd *cmd, t_token *token)
{
	int i;
	char *ret;
	char *new_value;

	i = 0;
	if (token->str[0] == '$')
	{
		printf("DOLLARSIGN\n");
		ret = expansion_string(cmd, token->str, 0);
		free(token->str);
		token->str = NULL;
		if (ret != NULL)
			token->str = ft_strdup(ret);
		return ;
	}
	while (token->str && token->str[i])
	{
		if (token->str[i] == '$')
		{
			ret = expansion_string(cmd, token->str, i);
			printf("EXPAND TO ->%s\n", ret);
			printf("OLD vlaue %s\n", token->str);
			new_value = ft_substr(token->str, 0, i);
			free(token->str);
			token->str = ft_strjoin(new_value, ret);
			free(ret);
			free(new_value);
			printf("New vlaue %s\n", token->str);
			break;
		}
		i++;
	}
}

char *expansion_string(t_cmd *cmd, char *str, int index)
{
	char *string;
	t_env *node;

	string = ft_substr(str, ++index, ft_strlen(str));
	printf("IS THIS IN ENV -> %s\n", string);
	node = is_inside_envp(cmd->env, cmd, 0, string);
	if (node != NULL)
		return (node->key_value[1]);
	free(string);
	return (NULL);
}
