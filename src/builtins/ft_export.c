/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:21:14 by snocita           #+#    #+#             */
/*   Updated: 2023/07/04 14:20:29 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_value_before_equal(char	*str)
{
	char	*value;
	size_t	i;

	i = 0;
	if (ft_strchr(str, '=') == NULL)
	{
		printf("NO EQUAL\n");
		return (NULL);
	}
	printf("debug\n");
	while (str[i] && str[i] != '=')
		i++;
	printf("debug1\n");
	value = malloc(sizeof(char) * (i + 1));
	printf("debug2\n");
	if (!value)
		return (NULL);
	printf("debug3\n");
	i = 0;
	while (str[i] && str[i] != '=')
	{
		value[i] = str[i];
		i++;
	}
	printf("debug4\n");
	value[i] = '\0';
	printf("debug5\n");
	if (ft_strcmp(str, value) == 0)
	{
		free(value);
		return (NULL);
	}
	printf("debug6\n");
	return (value);
}


int	ft_export(t_cmd	*cmd, t_env	*envp)
{
	char	*to_export;
	char	*value;
	int		i;
	char	*to_substitute;
	t_env	*next_node;

	next_node = NULL;
	//does export have arg ? if yes, continue, else show env !!
	if (cmd->start->next == NULL)
	{
		ft_env(envp);
		return (1);
	}
	//printf("string is=> %s\n", cmd->start->next->str);
	to_export = NULL;
	to_export = ft_strdup(cmd->start->next->str);
	//printf("variable to export is -> %s\n", to_export);
	value = get_value_before_equal(to_export);
	if (value == NULL)
	{
		free(to_export);
		return (0);
	}
	//printf("Value is ->%s\n", value);
	i = 0;
	while (envp->next != NULL)
	{
		//printf("Comparing value -> %s\n", to_substitute);
		to_substitute = get_value_before_equal(envp->value);
		if (is_exact_match(to_substitute, value) == 1)
		{
			//printf("TO SUBSTITUTE -> %s\n", envp->value);
			next_node = malloc(sizeof(t_env));
			if (!next_node)
				return (1);
			next_node->value = ft_strdup(to_export);
			free(to_export);
			next_node->prev = envp;
			next_node->next = envp->next;
			if (envp->next != NULL)
				envp->next->prev = next_node;
			envp->next = next_node;
			free(value);
			return (1);
		}
		envp = envp->next;
	}
	//printf("NO MATCH FOUND, CREATE NEW NODE\n");
	next_node->value = ft_strdup(to_export);
	next_node->prev = envp;
	next_node->next = NULL;
	envp->next = next_node;
	return (1);
}
