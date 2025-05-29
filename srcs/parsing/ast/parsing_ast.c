/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:34:37 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/29 01:33:27 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	init_cmdfile(t_global *g, t_cmds *cmds, t_tok_nd *nd)
{
    cmds->file = join_subword(g, nd->next->top);
    cmds->redir = nd->type;
}

t_cmds	*new_cmds(t_global *g, t_tok_nd *start, t_tok_nd *end)
{
	t_cmds		*cmds;
	t_tok_nd	*cur;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		ft_exit("Malloc", g); // verif si il faut liberer des trucs en plus
	cur = start;
	ft_bzero(cmds, sizeof(t_cmds));
	while (1)
	{
		if (is_redir(cur->type))
		{
			init_cmdfile(g, cmds, cur);
			cur = cur->next;
		}
		else if (!is_parenthesis(cur->type))
            lstadd_back_cmd(g, &cmds->topcmd, cur->top);
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (cmds);
}

t_ast	*parsing_ast(t_global *g, t_tok_nd *start, t_tok_nd *end)
{
	t_ast		*nd_ast;
	t_tok_nd	*pivot;

    if (!start || !end)
        return (NULL);
	pivot = find_lowest_prio_op(start, end);
	if (!pivot)
    {
        pivot = get_first_cmd(start, end);
        if (!pivot || is_parenthesis(pivot->type))
            return (NULL);
		return (create_ast_cmd(g, pivot, end));
    }
	nd_ast = create_ast_op(g, pivot);
	nd_ast->left = parsing_ast(g, start, pivot->prev);
	nd_ast->right = parsing_ast(g, pivot->next, end);
	return (nd_ast);
}
