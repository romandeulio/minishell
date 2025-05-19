/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:58:25 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/19 16:09:13 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lstfree_token(t_tok_stk *p)
{
	t_tok_nd	*tmp;
	t_tok_nd	*cur;

	tmp = p->top;
	cur = p->top;
	while (cur)
	{
		cur = cur->next;
		free(tmp->word);
		free(tmp);
		tmp = cur;
	}
	p->top = NULL;
}

void	lstadd_back_token(t_tok_stk *stk, t_tok_nd *nd)
{
	t_tok_nd	*tmp;

    if (!*nd->word)
    {
        free(nd->word);
        free(nd);
        return ;
    }
	if (!stk->top)
	{
		stk->top = nd;
		return ;
	}
	else
	{
		tmp = stk->top;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = nd;
	}
}

t_tok_nd	*lstnew_nd_token(int size, t_global *g)
{
	t_tok_nd	*new;

	new = malloc(sizeof(t_tok_nd));
	if (!new)
		ft_exit("Malloc", g);
	new->word = malloc(sizeof(char) * (size + 1));
	if (!new->word)
		ft_exit("Malloc", g);
	new->next = NULL;
	return (new);
}
