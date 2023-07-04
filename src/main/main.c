/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:22:16 by snocita           #+#    #+#             */
/*   Updated: 2023/07/04 16:45:09 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	init_struct(int ac, char **av, char **envp, t_cmd *cmd)
{
	if (ac != 1)
		exit(1);
	(void) av;
	obtain_envp(cmd, envp);
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
		cmd.input = readline("\033[0;32mMinishelly$\033[0m ");
		if (strlen(cmd.input) > 0)
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
