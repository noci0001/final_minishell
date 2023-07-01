/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:55:11 by snocita           #+#    #+#             */
/*   Updated: 2023/07/01 13:02:28 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern char	**g_my_envp;

int	check_for_duplicates(char	*to_export)
{
	int		i;
	char	*value_in_envp;

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

char	**obtain_double_array(char **double_array)
{
	char	**ret;
	int		i;

	i = 0;
	while (double_array[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	ret[i] = (NULL);
	i = 0;
	while (double_array[i])
	{
		ret[i] = malloc(sizeof(char) * (ft_strlen(double_array[i]) + 1));
		if (!ret[i])
			return (NULL);
		strlcpy(ret[i], double_array[i], (ft_strlen(double_array[i]) + 1));
		i++;
	}
	return (ret);
}

//checks that separators are succeded by not separators
// if they do, error is thrown
int	check_line(t_cmd *cmd, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI")
			&& (!token->next || is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			if (token->next)
				ft_putstr_fd(token->next->str, 2);
			else
				return (0);
			ft_putendl_fd("'", 2);
			cmd->ret = 258;
			return (0);
		}
		if (is_types(token, "PE")
			&& (!token->prev || !token->next || is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			ft_putstr_fd(token->str, 2);
			ft_putendl_fd("'", 2);
			cmd->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

char	*ft_get_env(char	**envp, char	*value_to_fetch)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], value_to_fetch, \
			ft_strlen(value_to_fetch)) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}


