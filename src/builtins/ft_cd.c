/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:43:04 by snocita           #+#    #+#             */
/*   Updated: 2023/07/06 13:15:28 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_cd(t_cmd	*cmd, t_env	*env)
{
	char	*home;
	//char	*before_path;

	//(void)cmd;
	home = ft_get_env(env, "HOME");
	printf("HOME is -> %s\n", home);
	// if (is_arg_absent(cmd, env, 0) == 1)
	// {
	// 	if(chdir(home) == 1)
	// }
	return (1);
}
