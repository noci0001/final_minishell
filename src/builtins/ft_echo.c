/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:21:01 by snocita           #+#    #+#             */
/*   Updated: 2023/07/09 13:12:39 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	loop_through_tokens(t_token	*token)
{
	int	print_new_line;

	print_new_line = 1;
	token = token->next;
	while (token->str != NULL && token->type == ARG)
	{
		if (token->str[0] == '-' && token->str[1] == 'n')
		{
			token = token->next;
			print_new_line = 0;
		}
		ft_putstr_fd(token->str, 1);
		if (token->next != NULL)
		{
			ft_putchar_fd(' ', 1);
			token = token->next;
		}
		else
		{
			if (print_new_line != 0)
				ft_putchar_fd('\n', 1);
			return (1);
		}
	}
	return (1);
}

int	ft_echo(t_token *token, t_cmd *cmd, t_env *env)
{
	if (is_arg_absent(cmd, env, 0) == 1)
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	loop_through_tokensy(token);
	return (1);
}
