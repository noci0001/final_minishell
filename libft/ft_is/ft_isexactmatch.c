/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isexactmatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:01:35 by snocita           #+#    #+#             */
/*   Updated: 2023/07/03 14:01:56 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int is_exact_match(char *x_str, char *y_str)
{
    int is_x_equal_to_y;
    int is_y_equal_to_x;

    is_x_equal_to_y = ft_strncmp(x_str, y_str, ft_strlen(x_str));
    is_y_equal_to_x = ft_strncmp(x_str, y_str, ft_strlen(y_str));
    
    if (is_x_equal_to_y == 0 && is_y_equal_to_x == 0)
        return (1);
    return (0);    
}
