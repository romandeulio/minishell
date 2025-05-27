/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:58:12 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/27 16:23:16 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_operator_endline(t_tok_stk *stk)
{
	t_tok_nd	*nd;
	t_type		type;

	nd = lstget_last_nd_tok(stk->top);
	if (!nd)
		return (0);
	type = nd->type;
	return (is_operator(type));
}

int	is_end_line(t_tok_stk *stk)
{
	if (stk->paren_lvl == 0 && stk->state == NORMAL
		&& stk->backslash == 0 && !is_operator_endline(stk))
		return (1);
	return (0);
}

void	add_semicolon(t_global *g)
{
	t_tok_nd	*nd;

	nd = lstnew_nd_tok(g);
	nd->type = SEMICOLON;
	nd->top = lstnew_nd_subtok(1, g);
	nd->top->subword[0] = ';';
	nd->top->subword[1] = '\0';
	nd->top->state = NORMAL; // Deja obligatoirement sur NORMAL je crois
	lstadd_back_tok(&g->tok_stk, nd);
}

void add_nl_last_nd(t_global *g)
{
	t_tok_nd *last_nd;
	t_subtok *last_subtok;
	char *new;

	last_nd = lstget_last_nd_tok(g->tok_stk.top);
	if (!last_nd)
		return ;
	last_subtok = lstget_last_nd_subtok(last_nd->top);
	if (!last_subtok)
		return ;
	new = ft_strjoin(last_subtok->subword, "\n");
	if (!new)
		ft_exit("Malloc", g);
	free(last_subtok->subword);
	last_subtok->subword = new;
}
