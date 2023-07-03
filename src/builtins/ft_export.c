/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:21:14 by snocita           #+#    #+#             */
/*   Updated: 2023/07/03 15:57:36 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
	if (ft_strcmp(str, value) == 0)
		return (NULL);
	return (value);
}

// char	**increase_envp(char **envp, char  *toadd)
// {
// 	int		i;
// 	char	**ret;

// 	i = 0;
// 	while(envp[i])
// 		i++;
// 	i++;
// 	ret = malloc(sizeof(char) + i + 1);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		ret[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	ret[i] = ft_strdup(toadd);
// 	i++;
// 	ret[i] = NULL;
// 	return (ret);
// }

// void	update_envp(char	*value_to_add)
// {
// 	int		index;
// 	char	**envp_temp;

// 	index = check_for_duplicates(value_to_add);
// 	if (index == -1)
// 	{
// 		//printf("Matching not found!\n");
// 		envp_temp = obtain_double_array(g_my_envp);
// 		free(g_my_envp);
// 		g_my_envp = increase_envp(envp_temp, value_to_add);
// 	}
// 	else
// 	{
// 		//printf("Matching found\n");
// 		free(g_my_envp[index]);
// 		g_my_envp[index] = ft_strdup(value_to_add);
// 		//printf("SUBSTITUTION MADE -> %s\n", g_my_envp[index]);
// 	}
// 	return ;
// }

// int	ft_export(t_token	*token)
// {
// 	token = token->next;
// 	if (token->next == NULL)
// 	{
// 		//printf("Value is -> %s\n", export_arg);
// 		update_envp(token->str);
// 		//print_double_array(g_my_envp);
// 		// if (check_for_duplicates(export_arg) == 1)
// 		// 	printf("NO DUPS FOUND!\n");
// 	}
// 	return (0);
// }

int	ft_export(t_cmd	*cmd, t_env	*envp)
{
	char	*to_export;
	char	*value;
	int		i;
	char	*to_substitute;
	t_env	*next_node;
	
	printf("string is=>%s\n", cmd->start->next->str);
	next_node = malloc(sizeof(t_env));
	if (!next_node)
		return (0);
	to_export = NULL;
	//does export have arg ? if yes, continue, else show env !!
	if (cmd->start->next == NULL)
	{
		ft_env(envp);
		return (1);	
	}
	to_export = cmd->start->next->str;
	printf("variable to export is -> %s\n", to_export);
	value = get_value_before_equal(to_export);
	if (value == NULL)
	{
		free(value);
		return (0);
	}
	printf("Value is ->%s\n", value);
	i = 0;
	while (envp->next != NULL)
	{
	printf("Comparing value -> %s\n", to_substitute);
		to_substitute = get_value_before_equal(envp->value);
		if (is_exact_match(to_substitute, value) == 1)
		{
			printf("TO SUBSTITUTE -> %s\n", envp->value);
			next_node = envp->next;
			free(envp->value);
			envp->value = ft_strdup(to_export);
			printf("NEW VALUE IS ->%s\n", to_export);
			envp->next = next_node;
			return (1);
		}
		envp = envp->next;
	}
	printf("NO MATCH FOUND, CREATE NEW NODE\n");
	next_node->value = ft_strdup(to_export);
	next_node->prev = envp;
	next_node->next = NULL;
	envp->next = next_node;
	return (1);
}
