/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delimiter_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:22:01 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/19 21:59:44 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_parentheses(t_global *g, t_tok_nd *nd)
{
	t_tok_stk	*stk;

	stk = &g->tok_stk;
	if (nd->type == PAREN_OPEN)
		stk->parenthesis++;
	else if (nd->type == PAREN_CLOSE)
		stk->parenthesis--;
	if (stk->parenthesis == -1)
	{
		write_error_syntax(nd->word);
		ft_exit(NULL, g);
	}
}

// void	handle_quote(t_global *g, t_tok_nd *nd)
// {
// 	t_tok_stk	*stk;

// 	stk = &g->tok_stk;
// 	if (nd->state == SQ)
// 		stk->sq = 1;
// 	else if (nd->state == DQ)
// 		stk->dq = 1;
// }
