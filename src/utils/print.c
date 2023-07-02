/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:19:43 by snocita           #+#    #+#             */
/*   Updated: 2023/07/02 15:50:36 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_double_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		printf("%s ", str[i++]);
	return ;
}
