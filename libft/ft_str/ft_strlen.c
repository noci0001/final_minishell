/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:14:35 by snocita           #+#    #+#             */
/*   Updated: 2023/06/30 19:11:53 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "../libft.h"

/*

	What are you even doing if you don't know this one?

*/

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (*s)
	{
		s++;
		length += 1;
	}
	return (length);
}
