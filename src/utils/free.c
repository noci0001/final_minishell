/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:58:40 by snocita           #+#    #+#             */
/*   Updated: 2023/06/30 12:47:16 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_token(t_token *start)
{
	while (start && start->next)
	{
		ft_memdel(start->str);
		start = start->next;
		ft_memdel(start->prev);
	}
	if (start)
	{
		ft_memdel(start->str);
		ft_memdel(start);
	}
}

void	free_double_arr(char **str)
{
	char	**temp;

	if (!str)
		return ;
	temp = str;
	while (*str)
	{
		if (*str && (*str != NULL))
			free(*str);
		str++;
	}
	if (temp != NULL)
		free(temp);
	return ;
}
