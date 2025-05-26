/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tok2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:58:25 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/24 01:23:33 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lstadd_back_tok(t_tok_stk *stk, t_tok_nd *nd)
{
	t_tok_nd	*tmp;

    // if (!*nd->word)
    // {
    //     free(nd->word);
    //     free(nd);
    //     return ;
    // }
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

t_tok_nd *lstget_last_nd_tok(t_tok_nd *top)
{
	t_tok_nd *tmp;

	if (!top)
		return (NULL);
	tmp = top;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	lstget_pos_nd_tok(t_tok_nd *cur, t_tok_nd *target)
{
	int	i;

	i = 0;
	while (cur)
	{
		if (cur == target)
			return (i);
		cur = cur->next;
		i++;
	}
	return (-1);
}

int lstcount_nd_tok(t_tok_stk *stk)
{
	int count;
	t_tok_nd *nd;

	count = 0;
	nd = stk->top;
	while (nd)
	{
		nd = nd->next;
		count++;
	}
	return (count);
}

void lstdel_last_nd_tok(t_tok_stk *stk)
{
    t_tok_nd *tmp;

    if (!stk->top)
        return ;
    tmp = stk->top;
    if (!tmp->next)
    {
        lstfree_subtok(&stk->top->top);
        free(stk->top);
        stk->top = NULL;
        return ;
    }
    while (tmp && tmp->next)
    {
        if (!tmp->next->next)
        {
			lstfree_subtok(&tmp->next->top);
            free(tmp->next);
            tmp->next = NULL;
            return ;
        }
        tmp = tmp->next;
    }
}
