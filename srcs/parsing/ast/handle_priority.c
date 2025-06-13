/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_priority.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:42:54 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:35:59 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	get_priority(t_tok_nd *nd)
{
	int	value;

	value = 0;
	if (nd->type == PAREN_OPEN)
		value = -5;
	if (nd->type == SEMICOLON)
		value = -4;
	else if (nd->type == OR)
		value = -3;
	else if (nd->type == AND)
		value = -2;
	else if (nd->type == PIPE)
		value = -1;
	value += (6 * nd->paren_lvl);
	return (value);
}

t_tok_nd	*get_first_cmd(t_tok_nd *start, t_tok_nd *end)
{
	t_tok_nd	*cur;

	cur = start;
	while (cur && cur != end && is_parenthesis(cur->type))
		cur = cur->next;
	if (!cur)
		return (NULL);
	return (cur);
}

t_tok_nd	*find_lowest_prio_op(t_tok_nd *start, t_tok_nd *end)
{
	t_tok_nd	*cur;
	t_tok_nd	*lowest_nd;

	cur = start;
	lowest_nd = start;
	while (1)
	{
		if (get_priority(cur) <= get_priority(lowest_nd))
		{
			if (cur->type != PAREN_CLOSE)
				lowest_nd = cur;
		}
		if (cur == end)
			break ;
		cur = cur->next;
	}
	if (lowest_nd->type == CMD)
		return (NULL);
	return (lowest_nd);
}
