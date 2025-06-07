/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:42:48 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/07 17:39:32 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast	*create_ast_cmd(t_global *g, t_tok_nd *start, t_tok_nd *end)
{
	t_ast		*new;
    
	new = malloc(sizeof(t_ast));
	if (!new)
		exit_free(g, "Malloc", -1, 1);
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
		exit_free(g, "Malloc", -1, 1);
	new->type = pivot->type;
	new->subshell_lvl = pivot->paren_lvl;
	new->cmds = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void free_ast(t_ast *ast)
{
    if (!ast)
        return ;
    free_ast(ast->left);
    free_ast(ast->right);
	if (ast->cmds)
	{
        if (ast->cmds->heredoc_fd != -1)
            close(ast->cmds->heredoc_fd);
        lstfree_cmd(ast->cmds->topcmd);
		free(ast->cmds->file);
	}
    free(ast->cmds);
    free(ast);
}
