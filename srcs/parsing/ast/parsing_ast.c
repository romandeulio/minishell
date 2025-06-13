/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:34:37 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:36:14 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_cmds	*new_cmds(t_global *g, t_tok_nd *start, t_tok_nd *end)
{
	t_cmds		*cmds;
	t_tok_nd	*cur;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		exit_free(g, "Malloc", -1, 1);
	cur = start;
	ft_bzero(cmds, sizeof(t_cmds));
	while (1)
	{
		if (is_redir(cur->type))
		{
			lstadd_back_file(g, &cmds->file, cur);
			cur = cur->next;
		}
		else if (!is_parenthesis(cur->type))
			lstadd_back_cmd(g, &cmds->topcmd, cur);
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
	if (pivot->type != PAREN_OPEN)
		nd_ast->left = parsing_ast(g, start, pivot->prev);
	nd_ast->right = parsing_ast(g, pivot->next, end);
	return (nd_ast);
}
