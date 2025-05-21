/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:08:58 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/21 18:06:28 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// Erreur de parsing a detecter :
// (TOKEN) Quote jamais refermer (pas obligatoire).
// (TOKEN) Parenthese non fermante ou parenthese fermante sans l'avoir ouvrir
// (AST) Un operateur logique au debut, a la fin,
//	ou plusieurs consequitifs. (a gerer dans l'arbe AST)
// (AST) Redirection sans cmd (mot autre qu'un separateur) qui suit la redirection
// (AST) Les parenthese ne doivent pas etre coller a des cmd

int	parse_loop(int *j, char *line, t_global *g, t_tok_nd *nd)
{
	int			i;
	t_tok_stk	*stk;

	i = 0;
	stk = &g->tok_stk;
	while (line[i])
	{
		if (handle_backslash(&line[i], &i, stk))
			nd->word[(*j)++] = line[i - 1];
		else if (handle_sq(&line[i], &i, stk) || handle_dq(&line[i], &i, stk))
			continue ;
		else if (handle_space_sep(&line[i], stk))
			break ;
		else if (handle_sep(&line[i], &i, g, nd))
			break ;
		else if (line[i])
		{
			check_dollar(*line, stk, nd);
			nd->word[(*j)++] = line[i++];
		}
	}
	return (i);
}

int	parsing_token(char *line, t_global *g, t_tok_nd *nd)
{
	int	j;
	int	i;

	j = ft_strlen(nd->word);
	i = parse_loop(&j, line, g, nd);
	if (nd->type == CMD)
		nd->word[j] = '\0';
	return (i);
}

void	check_end_line(t_global *g)
{
	while (!is_end_line(&g->tok_stk))
	{
		if (g->tok_stk.backslash == 1)
			handle_incomplete_bs(g);
		else if (is_operator_endline(&g->tok_stk))
			handle_incomplete_op(g);
		else if (g->tok_stk.dq || g->tok_stk.sq)
			handle_incomplete_quote(g);
		else
			handle_incomplete_parenthesis(g);
	}
	print_token(g);
}

void	parsing_tokens(t_global *g)
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
		while (handle_space_sep(&g->rd.line[i], stk))
			i++;
		size = count_size_token(&g->rd.line[i], stk);
		nd = get_nd(size, &g->rd.line[i], g);
		i += parsing_token(&g->rd.line[i], g, nd);
		lstadd_back_token(stk, nd);
	}
	check_end_line(g);
}
