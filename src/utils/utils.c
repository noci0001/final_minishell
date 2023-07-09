/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:10:18 by snocita           #+#    #+#             */
/*   Updated: 2023/07/09 16:46:46 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
		ft_strlcpy(ret[i], double_array[i], (ft_strlen(double_array[i]) + 1));
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
			unexpected_token_message(token, cmd, 1);
			return (0);
		}
		if (is_types(token, "PE")
			&& (!token->prev || !token->next || is_types(token->prev, "TAIPE")))
		{
			unexpected_token_message(token, cmd, 0);
			return (0);
		}
		token = token->next;
	}
	return (1);
}

char	*ft_get_env(t_env *env, char *value_to_fetch)
{
	while (env->value && env->next != NULL)
	{
		if (is_exact_match(env->key_value[0], value_to_fetch) == 1)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	check_splitted_env(t_cmd *cmd, char **splitted_env)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	while (splitted_env[i])
	{
		tmp1 = ft_strjoin(splitted_env[i], "/");
		tmp2 = ft_strjoin(tmp1, (cmd->start->str));
		free(tmp1);
		if (access(tmp2, X_OK) == 0)
		{
			if (cmd->start->type == 1)
				cmd->start->path = ft_strdup(tmp2);
			free_double_arr(splitted_env);
			free(tmp2);
			return (1);
		}
		free(tmp2);
		i++;
	}
	return (0);
}

int	cmd_validation(t_cmd	*cmd)
{
	char	*path;
	char	**splitted_env;

	if (cmd->start->str[0] == '.' && cmd->start->str[1] == '/'
		&& (access(cmd->start->str, X_OK) == 0))
	{
		cmd->start->path = cmd->start->str;
		return (1);
	}
	if (cmd->start->str[0] == '/' && (access(cmd->start->str, X_OK) == 0))
	{
		cmd->start->path = cmd->start->str;
		return (1);
	}
	path = ft_get_env(cmd->env, "PATH") + 4;
	splitted_env = ft_split(path, ':');
	if (check_splitted_env(cmd, splitted_env) == 1)
		return (1);
	free_double_arr(splitted_env);
	return (0);
}
