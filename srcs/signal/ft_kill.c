/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:14:15 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 17:32:24 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_kill(t_global *g, pid_t pid, int signal)
{
	lstfree_tok(&g->tok_stk);
	free_ast(g->ast);
	free_readline(g);
	rl_clear_history();
	if (kill(pid, signal) == -1)
		exit_free(g, "kill", -1, 1);
}
