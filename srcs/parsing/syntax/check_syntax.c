/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:02:00 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/10 11:50:51 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_start_err(t_tok_nd *first, t_global *g)
{
	if (is_operator(first->type))
	{
		write_syntax_error(g, first->top);
		return (1);
	}
	return (0);
}

int	check_middle_err(t_tok_nd *first, t_tok_nd *next, t_global *g)
{
	if (is_operator(first->type) && next && is_operator(next->type))
		write_syntax_error(g, next->top);
	else if (is_redir(first->type) && next && !is_cmd(next->type))
		write_syntax_error(g, first->next->top);
	else if (!is_operator(first->type) && !is_parenthesis(first->type) && next)
	{
		if (is_cmd(next->type) && next->next && next->next->type == PAREN_OPEN)
			write_syntax_error(g, next->next->top);
		else if (next->type == PAREN_OPEN && next->next)
			write_syntax_error(g, next->next->top);
		else if (next->type == PAREN_OPEN && !next->next)
			write_syntax_error_newline(g);
		else
			return (0);
	}
	else if (first->type == PAREN_CLOSE && next && is_cmd(next->type))
		write_syntax_error(g, next->top);
	else if (first->type == PAREN_OPEN && next && next->type == PAREN_CLOSE)
		write_syntax_error(g, next->top);
	else if (first->type == PAREN_CLOSE && next && next->type == PAREN_OPEN)
		write_syntax_error(g, next->top);
	else
		return (0);
	return (1);
}

int	check_end_err(t_tok_nd *first, t_global *g)
{
	if (is_operator(first->type) && !is_weak_op(first->type))
	{
		write_syntax_error(g, first->top);
		return (1);
	}
	else if (is_redir(first->type))
	{
		write_syntax_error_newline(g);
		return (1);
	}
	return (0);
}

int	check_syntax(t_global *g, int check)
{
	int			i;
	t_tok_stk	*stk;
	t_tok_nd	*first;
	t_tok_nd	*next;

	stk = &g->tok_stk;
	first = stk->top;
	i = 1;
	if (check_paren_err(g, first))
		return (1);
	while (first)
	{
		next = first->next;
		if (i == 1 && check_start_err(first, g))
			return (1);
		else if (check_middle_err(first, next, g))
			return (1);
		else if (check && i == lstcount_nd_tok(stk) && check_end_err(first, g))
			return (1);
		i++;
		first = next;
	}
	return (0);
}
