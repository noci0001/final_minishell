/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by              +#+  #+#    #+#             */
/*   Updated: 2023/07/09 15:52:12 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minishell.h"

void	increase_shlvl(t_env	*env, t_cmd	*cmd)
{
	t_env	*shlvl;
	char	*level;
	int		level_number;
	char	*itoa_string;

	shlvl = is_inside_envp(env, cmd, 0, "SHLVL");
	level = ft_strdup(shlvl->key_value[1]);
	level_number = ft_atoi(level);
	level_number++;
	free(shlvl->value);
	free(shlvl->key_value[1]);
	itoa_string = ft_itoa(level_number);
	shlvl->key_value[1] = ft_strdup(itoa_string);
	shlvl->value = ft_strjoin("SHLVL=", itoa_string);
	free(itoa_string);
	free(level);
}

void	init_struct(int ac, char **av, char **envp, t_cmd *cmd)
{
	if (ac != 1)
		exit(1);
	(void)av;
	obtain_envp(cmd, envp);
	sig_handler();
	increase_shlvl(cmd->env, cmd);
}

//echo -n hello there | cat -n | ls
int	main(int ac, char **av, char **envp)
{
	t_cmd	cmd;

	init_struct(ac, av, envp, &cmd);
	cmd.start = NULL;
	cmd.input = NULL;
	cmd.exit = 0;
	cmd.ret = 0;
	cmd.start = NULL;
	while (cmd.exit == 0)
	{
		sig_handler();
		cmd.input = readline("\033[0;32mMinishelly$\033[0m ");
		if (cmd.input && strlen(cmd.input) > 0)
			add_history(cmd.input);
		parse(cmd.input, &cmd);
		if (cmd.start != NULL && check_line(&cmd, cmd.start))
			execution(&cmd, cmd.start);
		free_token(cmd.start);
	}
	free_env(cmd.env);
	free(cmd.input);
	return (0);
}
