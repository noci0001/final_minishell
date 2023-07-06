/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:30:59 by snocita           #+#    #+#             */
/*   Updated: 2023/07/06 13:04:01 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_env	*env)
{
	char	*pwd;

	pwd = ft_get_env(env, "PWD");
	ft_putendl_fd(pwd + 5, 1);
	return (1);
}
