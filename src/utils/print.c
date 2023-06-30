/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:19:43 by snocita           #+#    #+#             */
/*   Updated: 2023/06/30 17:21:27 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void    print_double_array(char **str)
{
    int i;

    i = 0;
    while (str[i])
        printf("%s\n", str[i++]);
    return ;
}