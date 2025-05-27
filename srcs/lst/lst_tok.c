/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:51:30 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/28 00:37:36 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tok_nd	*lstnew_nd_tok(t_global *g)
{
	t_tok_nd	*new;

	new = malloc(sizeof(t_tok_nd));
	if (!new)
		ft_exit("Malloc", g);
	new->top = NULL;
	new->type = CMD;
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

// t_tok_nd	*lstnew_nd_tok(t_global *g)
// {
// 	t_tok_nd	*new;

// 	new = malloc(sizeof(t_tok_nd));
// 	if (!new)
// 		ft_exit("Malloc", g);
// 	new->word = malloc(sizeof(char) * (size + 1));
// 	if (!new->word)
// 		ft_exit("Malloc", g);
// 	new->word[0] = '\0';
//     new->type = CMD;
//     new->varenv = 0;
// 	new->next = NULL;
// 	return (new);
// }

// void	lstfree_tok(t_tok_stk *p)
// {
// 	t_tok_nd	*tmp;
// 	t_tok_nd	*cur;

// 	tmp = p->top;
// 	cur = p->top;
// 	while (cur)
// 	{
// 		cur = cur->next;
// 		free(tmp->word);
// 		free(tmp);
// 		tmp = cur;
// 	}
// 	p->top = NULL;
// }
