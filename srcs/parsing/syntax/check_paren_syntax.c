/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paren_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:19:25 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:37:05 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_double_paren(t_tok_nd *first, int lvl_ref)
{
	t_tok_nd	*cur;
	t_tok_nd	*next;
	int			lvl;

	cur = first;
	lvl = lvl_ref;
	while (cur)
	{
		next = cur->next;
		if (cur->type == PAREN_CLOSE && next && next->type == PAREN_CLOSE)
		{
			if (lvl == lvl_ref)
				return (1);
		}
		else if (cur->type == PAREN_OPEN)
			lvl++;
		else if (cur->type == PAREN_CLOSE)
			lvl--;
		cur = next;
	}
	return (0);
}

int	check_paren_expr(t_tok_nd *cur)
{
	t_tok_nd	*next;
	int			lvl;

	lvl = 0;
	while (cur)
	{
		next = cur->next;
		if (cur->type == PAREN_OPEN && next && next->type == PAREN_OPEN)
		{
			lvl += 2;
			if (check_double_paren(next->next, lvl))
				return (1);
		}
		else if (cur->type == PAREN_OPEN)
			lvl++;
		else if (cur->type == PAREN_CLOSE)
			lvl--;
		cur = next;
	}
	return (0);
}

int	check_paren_close(t_global *g, t_tok_nd *first)
{
	t_tok_nd	*cur;
	int			lvl;

	cur = first;
	lvl = 0;
	while (cur)
	{
		if (cur->type == PAREN_OPEN)
			lvl++;
		else if (cur->type == PAREN_CLOSE)
			lvl--;
		if (lvl < 0)
		{
			write_syntax_error(g, cur->top);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	check_paren_err(t_global *g, t_tok_nd *first)
{
	if (check_paren_close(g, first))
		return (1);
	return (0);
}
