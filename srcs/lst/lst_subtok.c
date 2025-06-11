/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_subtok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:45:55 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/11 16:23:48 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_subtok	*lstnew_nd_subtok(int size, t_global *g)
{
	t_subtok	*new;

	new = malloc(sizeof(t_subtok));
	if (!new)
		exit_free(g, "Malloc", -1, 1);
	new->subword = malloc(sizeof(char) * (size + 1));
	if (!new->subword)
		exit_free(g, "Malloc", -1, 1);
	new->subword[0] = '\0';
	new->state = g->tok_stk.state;
	new->varenv = 0;
	new->wildcard = 0;
	new->next = NULL;
	return (new);
}

void	lstfree_subtok(t_subtok **subtok)
{
	t_subtok	*tmp;
	t_subtok	*cur;

	tmp = *subtok;
	cur = *subtok;
	while (cur)
	{
		cur = cur->next;
		free(tmp->subword);
		free(tmp);
		tmp = cur;
	}
	*subtok = NULL;
}

t_subtok	*lstget_last_nd_subtok(t_subtok *top)
{
	t_subtok	*tmp;

	if (!top)
		return (NULL);
	tmp = top;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	lstadd_back_subtok(t_subtok **top, t_subtok *nd)
{
	t_subtok	*tmp;

	if (!*top)
	{
		*top = nd;
		return ;
	}
	tmp = *top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = nd;
}

void	lstdelete_subtok(t_subtok **top, t_subtok *dlt)
{
	t_subtok	*cur;
	t_subtok	*prev;

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
			free(cur->subword);
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}
