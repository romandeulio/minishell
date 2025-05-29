/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paren_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:19:25 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/28 23:41:15 by nicolasbrec      ###   ########.fr       */
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

int check_paren_close(t_global *g, t_tok_nd *first)
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
			close_line(cur->top, g);
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
    // J'enleve car je ne gere pas quand il y a plus de 2 parenthese d'affiler,
    // (Je ne sais pas encore comment gerer ca)
    // et je ne gere pas les espaces entre les doubles parenthese 
    // (facile a gerer, je peux rajouter un ou "((" ou "))")
    // else if (check_paren_expr(first))
    // {
    //     ft_putstr_fd("minishell: syntax error: ", 2);
    //     ft_putstr_fd("arithmetic commands ((...)) are not supported\n", 2);
    //     g->error_line = 1;
    //     return (1);
    // }
    return (0);
}
