/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:52:04 by nbrecque          #+#    #+#             */
/*   Updated: 2025/06/13 18:53:47 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lstreplace_nd_file(t_file **top, t_file *old, t_file *new)
{
	t_file	*cur;
	t_file	*prev;

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
