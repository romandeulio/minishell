/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:43:11 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/29 17:38:13 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	interpret_signal(t_global *g)
{
    if (g_signal == SIGINT && !g->is_interactive)
        ft_exit(g, "", 1, 130);
	else if (g_signal == SIGQUIT && !g->is_interactive)
        exit(131);
    g_signal = 0;
}

void	handler(int signum)
{
    if (signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
	g_signal = signum;
}

void	handle_signal(void)
{
	struct sigaction sig_quit;
	struct sigaction sig_int;
	
	sig_int.sa_handler = handler;
    sig_int.sa_flags = SA_RESTART;
    sigemptyset(&sig_int.sa_mask);
    sig_quit.sa_handler = handler;
    sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
