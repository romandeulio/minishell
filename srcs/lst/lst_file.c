/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:17:40 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:54:11 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_file	*lstnew_nd_file(t_global *g, t_tok_nd *nd)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		exit_free(g, "Malloc", -1, 1);
	if (nd)
	{
		new->subcmd = lstcpy_subtoks_subcmd(g, nd->next->top);
		new->heredoc_fd = nd->next->heredoc_fd;
		new->redir = nd->type;
	}
	else
	{
		new->subcmd = NULL;
		new->heredoc_fd = -1;
	}
	new->next = NULL;
	return (new);
}

void	lstfree_file(t_file *top)
{
	t_file	*cur;
	t_file	*tmp;

	cur = top;
	while (cur)
	{
		tmp = cur->next;
		lstfree_subcmd(&cur->subcmd);
		if (cur->heredoc_fd != -1)
			close(cur->heredoc_fd);
		free(cur);
		cur = tmp;
	}
}

void	lstadd_back_file(t_global *g, t_file **top, t_tok_nd *nd)
{
	t_file	*tmp;

	if (!*top)
	{
		*top = lstnew_nd_file(g, nd);
		return ;
	}
	tmp = *top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = lstnew_nd_file(g, nd);
}

t_file	*lstget_last_nd_file(t_file *top)
{
	t_file	*tmp;

	if (!top)
		return (NULL);
	tmp = top;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	lstdelete_file_nd(t_file **top, t_file *dlt)
{
	t_file	*cur;
	t_file	*prev;

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
