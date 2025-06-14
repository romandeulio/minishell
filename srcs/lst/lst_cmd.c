/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:38:00 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:49:56 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*lstnew_nd_cmd(t_global *g, t_tok_nd *nd)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_free(g, "Malloc", -1, 1);
	if (nd)
		new->subcmd = lstcpy_subtoks_subcmd(g, nd->top);
	else
		new->subcmd = NULL;
	new->next = NULL;
	return (new);
}

void	lstfree_cmd(t_cmd *top)
{
	t_cmd	*cur;
	t_cmd	*tmp;

	cur = top;
	while (cur)
	{
		tmp = cur->next;
		lstfree_subcmd(&cur->subcmd);
		free(cur);
		cur = tmp;
	}
}

void	lstadd_back_cmd(t_global *g, t_cmd **top, t_tok_nd *nd)
{
	t_cmd	*tmp;

	if (!*top)
	{
		*top = lstnew_nd_cmd(g, nd);
		return ;
	}
	tmp = *top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = lstnew_nd_cmd(g, nd);
}

void	lstdelete_cmd_nd(t_cmd **top, t_cmd *dlt)
{
	t_cmd	*cur;
	t_cmd	*prev;

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
