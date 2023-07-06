/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:21:01 by snocita           #+#    #+#             */
/*   Updated: 2023/07/06 11:29:18 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int ft_echo(t_token *token, t_cmd   *cmd, t_env *env)
{   
    int print_new_line = 1;
    if (is_arg_absent(cmd, env, 0) == 1)
        return (1);
    token = token->next;
    // if (token->str[0] == '$')
    //     printf("IS THIS DOLLARS SIGN? %c\n", token->str[0]);
    while (token->str != NULL && token->type == ARG)
    {
        if (token->str[0] == '-' && token->str[1] == 'n')
        {
            token = token->next;
            print_new_line = 0;
        }
        ft_putstr_fd(token->str, 1);
        if (token->next != NULL)
        {
            ft_putchar_fd(' ', 1);
            token = token->next;
        }
        else
        {
            if (print_new_line != 0)
                ft_putchar_fd('\n', 1);
            return (1);
        }
    }
    return (1);
}