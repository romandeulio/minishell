/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_termios.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:21:11 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:40:59 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	save_termios_state(t_global *g)
{
	tcgetattr(STDIN_FILENO, &g->original);
}

void	restore_termios_state(t_global *g)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g->original);
}

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	enable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
