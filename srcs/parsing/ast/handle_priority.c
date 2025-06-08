/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_priority.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:42:54 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/08 01:48:36 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// int	get_priority(t_tok_nd *nd)
// {
// 	int	value;

// 	value = 0;
// 	if (nd->type == SEMICOLON)
// 		value = -4;
// 	else if (nd->type == OR)
// 		value = -3;
// 	else if (nd->type == AND)
// 		value = -2;
// 	else if (nd->type == PIPE)
// 		value = -1;
// 	value += (5 * nd->paren_lvl);
// 	return (value);
// }

int	get_priority(t_tok_nd *nd)
{
	int	value;

    // printf("subword = %s\n", nd->top->subword);
    // printf("type = %d\n", nd->type);
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
    // printf("value = %d\n", value);
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
    // printf("\n\033[1;31mNouvelle branche :\033[0m\n");
    // printf("\033[1;31mstart = %p && subword = %s\033[0m\n", start, start->top->subword);
    // printf("\033[1;31mend = %p && subword = %s\033[0m\n\n", end, end->top->subword);
	while (1)
	{
        // printf("\n\033[1;32mComparaison :\033[0m\n\n");
		if (get_priority(cur) <= get_priority(lowest_nd))
		{
			if (cur->type != PAREN_CLOSE)
				lowest_nd = cur;
		}
		if (cur == end)
			break ;
		cur = cur->next;
	}
    // printf("lowest_nd->top->subword = %s\n", lowest_nd->top->subword);
	if (lowest_nd->type == CMD)
		return (NULL);
	return (lowest_nd);
}


// t_tok_nd	*find_lowest_prio_op(t_tok_nd *start, t_tok_nd *end)
// {
// 	t_tok_nd	*cur;
// 	t_tok_nd	*lowest_nd;

// 	cur = start;
// 	lowest_nd = get_first_cmd(start, end);
// 	if (!lowest_nd)
// 		return (NULL);
// 	// printf("\033[1;4;32mEND = %s\033[0m\n", end->top->subword);
// 	while (1)
// 	{
// 		// printf("\033[1;4;33mCUR :\033[0m\n");
// 		// printf("cur->top = %s\n", cur->top->subword);
// 		// printf("prio cur = %d\n", get_priority(cur));
// 		// printf("\033[1;4;33mLOWEST_ND :\033[0m\n");
// 		// printf("lowest_nd->top = %s\n", lowest_nd->top->subword);
// 		// printf("prio lowest_nd = %d\n", get_priority(lowest_nd));
// 		if (get_priority(cur) <= get_priority(lowest_nd))
// 		{
// 			// printf("\033[1;4;31mON EST RENTRER\033[0m\n");
// 			if (!is_parenthesis(cur->type))
// 				lowest_nd = cur;
// 		}
// 		if (cur == end)
// 			break ;
// 		cur = cur->next;
// 	}
// 	if (lowest_nd->type == CMD || is_parenthesis(lowest_nd->type))
// 		return (NULL);
// 	return (lowest_nd);
// }
