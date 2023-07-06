/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:43:04 by snocita           #+#    #+#             */
/*   Updated: 2023/07/06 12:44:26 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_cd(t_cmd	*cmd, t_env	*env)
{
	char	*home;

	(void)cmd;
	home = ft_get_env(env, "HOME");
	printf("HOME is -> %s\n", home);
	return (1);
}
