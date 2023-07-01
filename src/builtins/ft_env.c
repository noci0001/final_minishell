/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:21:22 by snocita           #+#    #+#             */
/*   Updated: 2023/07/01 15:02:44 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl(env->value);
		env = env->next;
	}
	if (env)
		ft_putendl(env->value);
	return (0);
}
