/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:30:59 by snocita           #+#    #+#             */
/*   Updated: 2023/07/08 15:14:17 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_env	*env)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_get_env(env, "PWD");
	oldpwd = ft_get_env(env, "OLDPWD");
	//should be pwd + 5!
	ft_putendl_fd(pwd, 1);
	ft_putendl_fd(oldpwd, 1);
	return (1);
}
