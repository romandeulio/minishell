/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:02:00 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/01 16:08:11 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_start_error(t_tok_nd *first, t_global *g)
{
	if (is_operator(first->type))
	{
		write_syntax_error(g, first->top);
		return (1);
	}
	return (0);
}

int	check_middle_error(t_tok_nd *first, t_tok_nd *next, t_global *g)
{
	if (is_operator(first->type) && next && is_operator(next->type))
		write_syntax_error(g, next->top);
	else if (is_redir(first->type) && next && !is_cmd(next->type))
		write_syntax_error(g, first->next->top);
	else if (is_cmd(first->type) && next && next->type == PAREN_OPEN)
		write_syntax_error(g, next->next->top);
	else if (first->type == PAREN_CLOSE && next && is_cmd(next->type))
		write_syntax_error(g, first->top);
    else if (first->type == PAREN_OPEN && next && next->type == PAREN_CLOSE)
		write_syntax_error(g, first->top);
    else if (first->type == PAREN_CLOSE && next && next->type == PAREN_OPEN)
		write_syntax_error(g, first->top);
    else
        return (0);
    return (1);
}

int	check_end_error(t_tok_nd *first, t_global *g)
{
	if (is_operator(first->type) && !is_weak_op(first->type))
	{
		write_syntax_error(g, first->top);
		return (1);
	}
	else if (is_redir(first->type))
	{
		g->error_line = 1;
		g->exit_code = 2;
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
		if (i == 1 && check_start_error(first, g))
			return (1);
		else if (check_middle_error(first, next, g))
			return (1);
		else if (check && i == lstcount_nd_tok(stk) && check_end_error(first,
				g))
			return (1);
		i++;
		first = next;
	}
	return (0);
}
