/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:50:33 by snocita           #+#    #+#             */
/*   Updated: 2023/07/20 12:08:29 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_sig	g_sig;

// check for open quotes
int	quote_check(t_cmd *cmd, char **line)
{
	if (quotes(*line, 2147483647))
	{
		printf("\033[0;32mMinishelly$\033[0m: syntax error with open quotes\n");
		ft_memdel(*line);
		cmd->ret = MISUSEOFBUILTINS;
		cmd->start = NULL;
		return (1);
	}
	return (0);
}

// takes input received through readline
//  and the struct.
void	parse(char *line, t_cmd *cmd)
{
	t_token	*token;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	if (g_sig.sigint == 1)
		cmd->ret = g_sig.exit_status;
	if (quote_check(cmd, &line))
		return ;
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

void	expansion_function(t_cmd	*cmd, t_token	*token)
{
	char	*ret;

	ret = expansion_string(cmd, token->str, 0);
	free(token->str);
	token->str = NULL;
	if (ret != NULL)
		token->str = ft_strdup(ret);
	return ;
}

void	check_expansion(t_cmd *cmd, t_token *token)
{
	int		i;
	char	*ret;
	char	*new_value;

	i = 0;
	if (token->str[0] == '$' && token->str[1] == '?')
	{
		cmd->start = NULL;
		return ((void)printf("Exit code: %d\n", cmd->ret));
	}
	else
	{
		if (token->str[0] == '$' && token->exp_disabled != 1)
			expansion_function(cmd, token);
	}
	while (token->str && token->str[i])
	{
		if (token->str[i] == '$' && token->exp_disabled != 1)
		{
			ret = expansion_string(cmd, token->str, i);
			new_value = ft_substr(token->str, 0, i);
			free(token->str);
			token->str = ft_strjoin(new_value, ret);
			free(ret);
			free(new_value);
			break ;
		}
		i++;
	}
}

char	*expansion_string(t_cmd *cmd, char *str, int index)
{
	char	*string;
	t_env	*node;

	string = ft_substr(str, ++index, ft_strlen(str));
	node = is_inside_envp(cmd->env, cmd, 0, string);
	if (node != NULL)
		return (node->key_value[1]);
	free(string);
	return (NULL);
}
