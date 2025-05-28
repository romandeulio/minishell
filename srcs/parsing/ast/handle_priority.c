/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_priority.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:42:54 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/28 14:10:46 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	get_priority(t_tok_nd *nd)
{
	int	value;

	value = 0;
	if (nd->type == SEMICOLON)
		value = -4;
	else if (nd->type == OR)
		value = -3;
	else if (nd->type == AND)
		value = -2;
	else if (nd->type == PIPE)
		value = -1;
	value += (5 * nd->paren_lvl);
	return (value);
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
			lowest_nd = cur;
		if (cur == end)
			break ;
		cur = cur->next;
	}
	if (get_priority(lowest_nd) == 0)
		return (NULL);
	return (lowest_nd);
}
