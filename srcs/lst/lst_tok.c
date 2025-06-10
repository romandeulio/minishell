/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:51:30 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/10 11:18:10 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tok_nd	*lstnew_nd_tok(t_global *g)
{
	t_tok_nd	*new;

	new = malloc(sizeof(t_tok_nd));
	if (!new)
		exit_free(g, "Malloc", -1, 1);
	new->top = NULL;
	new->type = CMD;
	new->heredoc_fd = -1;
	new->paren_lvl = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lstfree_tok(t_tok_stk *stk)
{
	t_tok_nd	*tmp;
	t_tok_nd	*cur;

	tmp = stk->top;
	cur = stk->top;
	while (cur)
	{
		cur = cur->next;
		lstfree_subtok(&tmp->top);
		free(tmp);
		tmp = cur;
	}
	stk->top = NULL;
}

void	lstinit_prev_node_tok(t_tok_nd *nd)
{
	t_tok_nd	*prev;

	prev = NULL;
	while (nd)
	{
		nd->prev = prev;
		prev = nd;
		nd = nd->next;
	}
}

void	lstdelete_tok_nd(t_tok_nd **top, t_tok_nd *dlt)
{
	t_tok_nd	*cur;
	t_tok_nd	*prev;

	if (!top || !*top || !dlt)
		return ;
	cur = *top;
	prev = NULL;
	while (cur)
	{
		if (cur == dlt)
		{
			if (!prev)
				*top = cur->next;
			else
				prev->next = cur->next;
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}
