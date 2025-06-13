/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:49:35 by nbrecque          #+#    #+#             */
/*   Updated: 2025/06/13 18:51:12 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lstreplace_nd_cmd(t_cmd **top, t_cmd *old, t_cmd *new)
{
	t_cmd	*cur;
	t_cmd	*prev;

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
			lstfree_subcmd(&cur->subcmd);
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

t_cmd	*lstget_last_nd_cmd(t_cmd *top)
{
	t_cmd	*tmp;

	if (!top)
		return (NULL);
	tmp = top;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}
