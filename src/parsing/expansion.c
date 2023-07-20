/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:29:23 by snocita           #+#    #+#             */
/*   Updated: 2023/07/10 17:37:51 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

void	check_for_exit_code(t_cmd	*cmd)
{
	cmd->start = NULL;
	(void)printf("Exit code: %d\n", cmd->ret);
	return ;
}
