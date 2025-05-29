/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:43:11 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/29 16:45:28 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	interpret_signal(t_global *g, int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (signum == SIGQUIT && !g->is_interactive)
		ft_exit(g, "Exit", 1, 0); // quitter le prg en exit(0) en faisant gaffe au leak etc..
}

void	handler(int signum)
{
	g_signal = signum;
}

void	handle_signal(void)
{
	struct sigaction sig_quit;
	struct sigaction sig_int;
	
	sig_int.sa_handler = handler;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}