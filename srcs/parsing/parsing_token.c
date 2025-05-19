/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:35:48 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/19 22:04:08 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Erreur de parsing a detecter :
// (TOKEN) Quote jamais refermer (pas obligatoire).
// (TOKEN) Parenthese non fermante ou parenthese fermante sans l'avoir ouvrir
// (AST) Un operateur logique au debut, a la fin,
//	ou plusieurs consequitifs. (a gerer dans l'arbe AST)
// (AST) Redirection sans cmd (mot autre qu'un separateur) qui suit la redirection
// (AST) Deux cmd d'affiler (compter aussi les cmd entre parentheses)

int	parsing_token2(char *line, t_tok_stk *stk, t_tok_nd *nd)
{
	if (nd->state == SQ)
		return (parsing_sq_state(line, stk, nd));
	else if (nd->state == DQ)
		return (parsing_dq_state(line, stk, nd));
	else if (nd->state == NORMAL && nd->type == 0)
		return (parsing_normal_state(line, nd));
	else
		return (parsing_separator(line, nd));
	return (0);
}

// A enlever si pas d'autre cas special (et gerer ca dans lstadd_back (if (!*nd->word)))
// int	handle_special_case(char *line, int *i, t_tok_stk *stk)
// {
// 	if (*line == '\'' && stk->sq == 0 && !line[1])
// 	{
// 		stk->sq = 1;
// 		(*i)++;
// 		return (1);
// 	}
// 	else if (*line == '\"' && stk->dq == 0 && !line[1])
// 	{
// 		stk->dq = 1;
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }

void	parsing_token(t_global *g)
{
	int			i;
	int			size;
	t_tok_stk	*stk;
	t_tok_nd	*nd;

	stk = &g->tok_stk;
	nd = stk->top;
	i = 0;
	while (g->rd.line[i])
	{
		while (incr_until_next_tok(&g->rd.line[i], stk))
			i++;
		size = token_len(&g->rd.line[i]);
		nd = lstnew_nd_token(size + 10, g);
		defined_type(&g->rd.line[i], nd);
		defined_state(&g->rd.line[i], nd, stk);
		i += parsing_token2(&g->rd.line[i], stk, nd);
		handle_parentheses(g, nd);
		lstadd_back_token(stk, nd);
		i += size;
	}
}
