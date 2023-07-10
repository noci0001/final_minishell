/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:32:31 by snocita           #+#    #+#             */
/*   Updated: 2023/07/10 09:59:48 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minishell.h"

void	sig_c(int signal)
{
	if (signal)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler(void)
{
	signal(SIGINT, sig_c);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_inprocess(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	turn_off_echo(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	else if (isatty(STDOUT_FILENO))
	{
		tcgetattr(STDOUT_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	}
	else if (isatty(STDERR_FILENO))
	{
		tcgetattr(STDERR_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDERR_FILENO, TCSANOW, &term);
	}
}
