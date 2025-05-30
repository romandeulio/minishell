/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:02:00 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/28 23:21:22 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_start_error(t_tok_nd *first, t_global *g)
{
	if (is_operator(first->type))
	{
		close_line(first->top, g);
		return (1);
	}
	return (0);
}

int	check_middle_error(t_tok_nd *first, t_tok_nd *next, t_global *g)
{
	if (is_operator(first->type) && next && is_operator(next->type))
	{
		close_line(next->top, g);
		return (1);
	}
	else if (is_redir(first->type) && next && !is_cmd(next->type))
	{
		close_line(first->next->top, g);
		return (1);
	}
	else if (is_cmd(first->type) && next && next->type == PAREN_OPEN)
	{
		close_line(next->next->top, g);
		return (1);
	}
	else if (first->type == PAREN_CLOSE && next && is_cmd(next->type))
	{
		close_line(first->top, g);
		return (1);
	}
	return (0);
}

int	check_end_error(t_tok_nd *first, t_global *g)
{
	if (is_operator(first->type) && !is_weak_op(first->type))
	{
		close_line(first->top, g);
		return (1);
	}
	else if (is_redir(first->type))
	{
		g->error_line = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
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
		if (check && i == 1 && check_start_error(first, g))
			return (1);
		else if (check && heck_middle_error(first, next, g))
			return (1);
		else if (check && i == lstcount_nd_tok(stk) && check_end_error(first,
				g))
			return (1);
		i++;
		first = next;
	}
	return (0);
}
