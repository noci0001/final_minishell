/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:25:37 by snocita           #+#    #+#             */
/*   Updated: 2023/07/04 15:23:31 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
// #include <stdio.h>

/*

	Takes a non-modifiable string,
	returns the same string in
	another variable

*/

size_t	ft_strlen(const char *s);

char	*ft_strdup(const char *s1)
{
	int		index;
	char	*scpy;

	scpy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!scpy)
		return (NULL);
	index = 0;
	while (s1[index])
	{
		scpy[index] = s1[index];
		index++;
	}
	scpy[index] = '\0';
	return (scpy);
}

// Free the memory allocated by ft_strdup
void	ft_strdel(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

// int	main(void)
// {
// 	char str[] = "Hello";
// 	printf("%s\n", ft_strdup(str));
// 	printf("%s\n", strdup(str));
// }
