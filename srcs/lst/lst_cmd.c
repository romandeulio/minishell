/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:38:00 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/30 13:34:55 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*lstnew_nd_cmd(t_global *g, t_subtok *nd)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		ft_exit(g, "Malloc", -1, 1);
	new->subtok = nd;
	new->next = NULL;
	return (new);
}

void	free_cmd(t_cmd *top)
{
	t_cmd	*cur;
	t_cmd	*tmp;

	cur = top;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
}

void	lstadd_back_cmd(t_global *g, t_cmd **top, t_subtok *nd)
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
