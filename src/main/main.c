#include "../headers/minishell.h"

extern char	**g_my_envp;

int	is_builtin(t_cmd	*cmd)
{
	// if (ft_strcmp(cmd.start->str, "cd") == 0)
	// 	return (ft_cd(cmd.start));
	if (ft_strcmp(cmd->start->str, "echo") == 0)
		return (ft_echo(cmd->start));
	if (ft_strcmp(cmd->start->str, "export") == 0)
		return (ft_export(cmd->start));
	if (ft_strcmp(cmd->start->str, "env") == 0)
		return (ft_env(g_my_envp));
	if (ft_strcmp(cmd->start->str, "exit") == 0)
	{
		cmd->exit = 1;
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
    (void)av;
	char	*input;
    t_cmd   cmd;

	if (ac != 1)
		return (0);
	ft_debug();
	g_my_envp = obtain_envp(envp);
	printf("\necho -n hello there | cat -n | ls\n");
	while (cmd.exit == 0)
	{
		input = readline("Minishelly$ ");
		if (strlen(input) > 0)
			add_history(input);
		parse(input, &cmd);
		if (cmd.start != NULL && check_line(&cmd, cmd.start))
		{
			if (is_builtin(&cmd) == 1)
				printf("builtin executed!\n");
				// execute();
		}
		free_token(cmd.start);
	}
	free_double_arr(g_my_envp);
	free(input);
	return (0);
}
