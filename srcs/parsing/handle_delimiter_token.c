/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delimiter_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:22:01 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/19 00:49:10 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_parenthese(t_global *g, t_tok_nd *nd)
{
	t_tok_stk	*stk;

	stk = &g->tok_stk;
	if (nd->type == PAREN_OPEN)
		stk->parenthese++;
	else if (nd->type == PAREN_CLOSE)
		stk->parenthese--;
	if (stk->parenthese == -1)
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
