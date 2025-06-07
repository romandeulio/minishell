/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:15:24 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/07 01:44:47 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	handle_dlt_subtok(t_subtok **top, t_subtok **subtok)
{
	t_subtok	*tmp;

	if (!(*subtok)->subword[0])
	{
		tmp = *subtok;
		*subtok = (*subtok)->next;
		lstdelete_subtok(top, tmp);
		return (1);
	}
	return (0);
}

int	handle_dlt_cmd_nd(t_cmd **top, t_cmd **cur)
{
	t_cmd   *tmp;

	if (!(*cur)->subtok)
	{
		tmp = *cur;
		*cur = (*cur)->next;
		lstdelete_cmd_nd(top, tmp);
		return (1);
	}
	return (0);
}

// int	handle_dlt_tok_nd(t_tok_nd **top, t_tok_nd **tok_nd)
// {
// 	t_tok_nd	*tmp;

// 	if (!(*tok_nd)->top)
// 	{
// 		tmp = *tok_nd;
// 		*tok_nd = (*tok_nd)->next;
// 		lstdelete_tok_nd(top, tmp);
// 		return (1);
// 	}
// 	return (0);
// }
