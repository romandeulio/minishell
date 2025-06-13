/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:20:31 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 17:33:09 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_endline_error(t_global *g)
{
	t_state	state;

	g->error_line = 1;
	g_exit_code = 2;
	state = g->tok_stk.state;
	if (state != NORMAL)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching", 2);
		if (state == SQ)
			ft_putstr_fd(" `\''\n", 2);
		else if (state == DQ)
			ft_putstr_fd(" `\"'\n", 2);
	}
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
}

void	write_syntax_error(t_global *g, t_subtok *subtok)
{
	g->error_line = 1;
	g_exit_code = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	while (subtok)
	{
		ft_putstr_fd(subtok->subword, 2);
		subtok = subtok->next;
	}
	ft_putstr_fd("'\n", 2);
}

void	write_syntax_error_newline(t_global *g)
{
	g->error_line = 1;
	g_exit_code = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}
