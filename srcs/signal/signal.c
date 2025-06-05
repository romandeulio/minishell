/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:43:11 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/04 20:36:31 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	interpret_signal(t_global *g)
{
	if (g_signal == SIGINT && !g->is_interactive)
		ft_kill(g, 0, SIGINT);
	else if (g_signal == SIGQUIT && !g->is_interactive)
		ft_kill(g, 0, SIGQUIT);
	g_signal = 0;
}
// Fonction a mettre apres tout nos fork, en mode non interactif
void	handle_sig_no_interactif(void)
{
	pid_t	pid;
	int		status;
	int		sig;
	int		last_sig;
	int		last_code;

	last_sig = 0;
	last_code = 0;
	pid = 1;
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0); // exit si waitpid echoue
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT || sig == SIGQUIT)
				last_sig = sig;
		}
		else if (WIFEXITED(status))
			last_code = WEXITSTATUS(status);
	}
	if (last_sig)
		kill(0, last_sig); // faire une fonction qui kill
							// et libere la memoire du parent
	exit(last_code);
}

void	handle_signal(t_global *g)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	if (g->is_interactive)
	{
		sig_int.sa_flags = SA_RESTART;
		sigemptyset(&sig_int.sa_mask);
		sig_int.sa_handler = sigint_handler;
		sig_quit.sa_flags = SA_RESTART;
		sigemptyset(&sig_quit.sa_mask);
		sig_quit.sa_handler = SIG_IGN;
	}
	else
	{
		sig_int.sa_flags = 0;
		sigemptyset(&sig_int.sa_mask);
		sig_int.sa_handler = handler_no_interactif;
		sig_quit.sa_flags = 0;
		sigemptyset(&sig_quit.sa_mask);
		sig_quit.sa_handler = handler_no_interactif;
	}
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
