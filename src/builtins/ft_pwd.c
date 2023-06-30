/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:30:59 by snocita           #+#    #+#             */
/*   Updated: 2023/06/30 18:12:19 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern char	**g_my_envp;

int	ft_pwd(char **g_my_envp)
{
	char	*pwd;

	pwd = ft_get_env(g_my_envp, "PWD=");
	ft_putendl_fd(pwd, 1);
	return (1);
}
