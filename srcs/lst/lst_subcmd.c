/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_subcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:01:05 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/11 01:53:14 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_subcmd	*lstcpy_all_subtok(t_global *g, t_subtok *subtok)
{
	t_subcmd	*last;
	t_subcmd	*new;
	int			size;

	new = NULL;
	while (subtok)
	{
		size = ft_strlen(subtok->subword);
		lstadd_back_subcmd(&new, lstnew_nd_subcmd(g, size));
		last = lstget_last_nd_subcmd(new);
		ft_strcpy(last->subword, subtok->subword);
		last->state = subtok->state;
		last->varenv = subtok->varenv;
		last->wildcard = subtok->wildcard;
		subtok = subtok->next;
	}
	return (new);
}

t_subcmd	*lstnew_nd_subcmd(t_global *g, int size)
{
	t_subcmd	*new;

	new = malloc(sizeof(t_subcmd));
	if (!new)
		exit_free(g, "Malloc", -1, 1);
	new->subword = malloc(sizeof(char) * (size + 1));
	if (!new->subword)
		exit_free(g, "Malloc", -1, 1);
	new->subword[0] = '\0';
	new->state = NORMAL;
	new->varenv = 0;
	new->wildcard = 0;
	new->next = NULL;
	return (new);
}

void	lstfree_subcmd(t_subcmd **subcmd)
{
	t_subcmd	*tmp;
	t_subcmd	*cur;

	tmp = *subcmd;
	cur = *subcmd;
	while (cur)
	{
		cur = cur->next;
		free(tmp->subword);
		free(tmp);
		tmp = cur;
	}
	*subcmd = NULL;
}

void	lstadd_back_subcmd(t_subcmd **top, t_subcmd *nd)
{
	t_subcmd	*tmp;

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

void	lstdelete_subcmd(t_subcmd **top, t_subcmd *dlt)
{
	t_subcmd	*cur;
	t_subcmd	*prev;

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

t_subcmd	*lstget_last_nd_subcmd(t_subcmd *top)
{
	t_subcmd	*tmp;

	if (!top)
		return (NULL);
	tmp = top;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}
