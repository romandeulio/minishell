/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:58:12 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/21 16:03:39 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_operator_endline(t_tok_stk *stk)
{
	t_tok_nd	*nd;
	t_type		type;

	nd = lstget_last_nd(stk);
	if (!nd)
		return (0);
	type = lstget_last_nd(stk)->type;
	return (is_operator(type));
}

int	is_end_line(t_tok_stk *stk)
{
	if (stk->parenthesis == 0 && stk->sq == 0 && stk->dq == 0
		&& stk->backslash == 0 && !is_operator_endline(stk))
		return (1);
	return (0);
}

void	add_semicolon(t_global *g)
{
	t_tok_nd	*nd;

	nd = lstnew_nd_token(1, g);
	nd->type = SEMICOLON;
	nd->varenv = 0;
	nd->word[0] = ';';
	nd->word[1] = '\0';
	lstadd_back_token(&g->tok_stk, nd);
}

void add_nl_last_nd(t_global *g)
{
	t_tok_nd *last;
	char *new;

	last = lstget_last_nd(&g->tok_stk);
	if (!last)
		return ;
	new = ft_strjoin(last->word, "\n");
	if (!new)
		ft_exit("Malloc", g);
	free(last->word);
	last->word = new;
}
