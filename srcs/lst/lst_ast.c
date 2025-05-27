/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:42:48 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/28 00:37:30 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// t_tok_nd	*lstget_nd_index(t_tok_nd *cur, int index)
// {
// 	int	i;

// 	if (index < 0)
// 		return (NULL);
// 	i = 0;
// 	while (cur)
// 	{
// 		if (i == index)
// 			return (cur);
// 		cur = cur->next;
// 		i++;
// 	}
// 	return (NULL);
// }

// int	lstget_idx_nd(t_tok_nd *cur, t_tok_nd *target)
// {
// 	int	i;

// 	i = 0;
// 	while (cur)
// 	{
// 		if (cur == target)
// 			return (i);
// 		cur = cur->next;
// 		i++;
// 	}
// 	return (-1);
// }