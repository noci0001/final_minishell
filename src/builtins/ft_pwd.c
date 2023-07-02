/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:30:59 by snocita           #+#    #+#             */
/*   Updated: 2023/07/02 15:20:02 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_env	*env)
{
	char	*pwd;

	pwd = ft_get_env(env, "PWD=");
	ft_putendl_fd(pwd + 5, 1);
	return (1);
}
