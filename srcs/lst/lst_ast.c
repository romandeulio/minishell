/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:42:48 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/28 12:47:59 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast	*create_ast_cmd(t_global *g, t_tok_nd *start, t_tok_nd *end)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		ft_exit("Malloc", g);
	new->type = CMD;
	new->subshell_lvl = start->paren_lvl;
	new->cmds = new_cmds(g, start, end);
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast	*create_ast_op(t_global *g, t_tok_nd *pivot)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		ft_exit("Malloc", g);
	new->type = pivot->type;
	new->subshell_lvl = pivot->paren_lvl;
	new->cmds = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
