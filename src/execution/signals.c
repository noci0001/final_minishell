/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <samuelnocita@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:32:31 by snocita           #+#    #+#             */
/*   Updated: 2023/07/08 19:52:10 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void sig_c(int signal)
{
    if (signal)
    {
        // rl_replace_line("", 0);
        ft_putchar_fd('\n', STDOUT_FILENO);
        rl_on_new_line();
        rl_redisplay();
    }
}
void sig_d(int signal)
{
    if (signal)
    {
        exit(1);
    }
}


void sig_handler(void)
{
    signal(SIGINT, sig_c);
    signal(SIGTSTP, sig_d);
    signal(SIGQUIT, SIG_IGN);
}

// can be usefull in procesess
// void	signal_inprocess(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }