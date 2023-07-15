/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:03:05 by snocita           #+#    #+#             */
/*   Updated: 2023/07/10 21:21:21 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_arg_absent(t_cmd	*cmd, t_env	*envp, int check)
{
	if ((cmd->start->next == NULL) && envp && (check == UNSET))
		return (1);
	if ((cmd->start->next == NULL) && envp)
	{
		ft_env(envp);
		return (1);
	}
	return (0);
}

size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

int	unexpected_token_message(t_token	*token, t_cmd	*cmd, int version)
{
	if (version == 1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		if (token->next)
			ft_putstr_fd(token->next->str, 2);
		else
			return (0);
		ft_putendl_fd("'", 2);
		cmd->ret = 258;
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->str, 2);
		ft_putendl_fd("'", 2);
		cmd->ret = 258;
	}
	return (0);
}