/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:15:24 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:36:41 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	handle_dlt_subcmd(t_subcmd **top, t_subcmd **subcmd)
{
	t_subcmd	*tmp;

	if (!(*subcmd)->subword[0])
	{
		tmp = *subcmd;
		*subcmd = (*subcmd)->next;
		lstdelete_subcmd(top, tmp);
		return (1);
	}
	return (0);
}

int	handle_dlt_file_nd(t_file **top, t_file **cur)
{
	t_file	*tmp;

	if (!(*cur)->subcmd)
	{
		tmp = *cur;
		*cur = (*cur)->next;
		lstdelete_file_nd(top, tmp);
		return (1);
	}
	return (0);
}

int	handle_dlt_cmd_nd(t_cmd **top, t_cmd **cur)
{
	t_cmd	*tmp;

	if (!(*cur)->subcmd)
	{
		tmp = *cur;
		*cur = (*cur)->next;
		lstdelete_cmd_nd(top, tmp);
		return (1);
	}
	return (0);
}
