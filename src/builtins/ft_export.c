/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:21:14 by snocita           #+#    #+#             */
/*   Updated: 2023/06/30 17:55:36 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**g_my_envp;

char	**obtain_envp(char **envp)
{
	g_my_envp = obtain_double_array(envp);
	return (g_my_envp);
}

int	check_for_duplicates(char	*to_export)
{
	int	i;
	char *value_in_envp;

	i = 0;
	while (g_my_envp[i])
	{
		value_in_envp = get_value_before_equal(g_my_envp[i]);	
		if (ft_strncmp(value_in_envp, to_export, ft_strlen(value_in_envp)) == 0)
			return (i);	
		i++;
	}
	return (-1);
}

char	*get_value_before_equal(char	*str)
{
	char	*value;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	value = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		value[i] = str[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

char	**increase_envp(char **envp, char  *toadd)
{
	int		i;
	char	**ret;

	i = 0;
	while(envp[i])
		i++;
	i++;
	ret = malloc(sizeof(char) + i + 1);
	i = 0;
	while (envp[i])
	{
		ret[i] = ft_strdup(envp[i]);
		i++;
	}
	ret[i] = ft_strdup(toadd);
	i++;
	ret[i] = NULL;
	return (ret);
}

void update_envp(char	*value_to_add)
{
	int index;
	char **envp_temp;
	index = check_for_duplicates(value_to_add);
	if (index == -1)
	{
		//printf("Matching not found!\n");
		envp_temp = obtain_double_array(g_my_envp);
		free(g_my_envp);
		g_my_envp = increase_envp(envp_temp, value_to_add);
	}
	else
	{
		//printf("Matching found\n");
		free(g_my_envp[index]);
		g_my_envp[index] = ft_strdup(value_to_add);
		//printf("SUBSTITUTION MADE -> %s\n", g_my_envp[index]);
	}
	return ;
}

int	ft_export(t_token	*token)
{
	token = token->next;
	if (token->next == NULL)
	{
		//printf("Value is -> %s\n", export_arg);
		update_envp(token->str);
		//print_double_array(g_my_envp);
		// if (check_for_duplicates(export_arg) == 1)
		// 	printf("NO DUPS FOUND!\n");
	}
	return (0);
}
