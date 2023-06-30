/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:21:01 by snocita           #+#    #+#             */
/*   Updated: 2023/06/30 17:59:46 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int ft_echo(t_token *token)
{   
    int print_new_line = 1;
    token = token->next;
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