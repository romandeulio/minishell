/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:42:48 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/11 22:10:05 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast	*create_ast_cmd(t_global *g, t_tok_nd *start, t_tok_nd *end)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		exit_free(g, "Malloc", -1, 1);
	new->type = CMD;
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
		exit_free(g, "Malloc", -1, 1);
	new->type = pivot->type;
	new->cmds = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	if (ast->cmds)
	{
		lstfree_file(ast->cmds->file);
		lstfree_cmd(ast->cmds->topcmd);
	}
	free(ast->cmds);
	free(ast);
}
