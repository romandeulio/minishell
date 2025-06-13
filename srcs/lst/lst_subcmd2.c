/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_subcmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:54:43 by nbrecque          #+#    #+#             */
/*   Updated: 2025/06/13 18:57:24 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_subcmd	*lstcpy_subcmd(t_global *g, t_subcmd *subcmd)
{
	t_subcmd	*last;
	t_subcmd	*new;
	int			size;

	new = NULL;
	while (subcmd)
	{
		size = ft_strlen(subcmd->subword);
		lstadd_back_subcmd(&new, lstnew_nd_subcmd(g, size));
		last = lstget_last_nd_subcmd(new);
		ft_strcpy(last->subword, subcmd->subword);
		last->state = subcmd->state;
		last->varenv = subcmd->varenv;
		last->wildcard = subcmd->wildcard;
		subcmd = subcmd->next;
	}
	return (new);
}

t_subcmd	*lstcpy_subtoks_subcmd(t_global *g, t_subtok *subtok)
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

void	lstreplace_nd_subcmd(t_subcmd **top, t_subcmd *old, t_subcmd *new)
{
	t_subcmd	*cur;
	t_subcmd	*prev;

	if (!top || !*top || !old || !new)
		return ;
	cur = *top;
	prev = NULL;
	while (cur)
	{
		if (cur == old)
		{
			if (!prev)
				*top = new;
			else
				prev->next = new;
			while (new && new->next)
				new = new->next;
			new->next = cur->next;
			free(cur->subword);
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}
