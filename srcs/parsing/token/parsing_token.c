/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:08:58 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/28 13:30:11 by nicolasbrec      ###   ########.fr       */
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

int	parse_subword(int *j, char *line, t_global *g, t_tok_nd *nd)
{
	int			i;
	t_tok_stk	*stk;
	t_subtok	*subtok;

	i = 0;
	stk = &g->tok_stk;
	subtok = lstget_last_nd_subtok(nd->top);
	while (line[i])
	{
		if (handle_backslash(&line[i], &i, stk))
			subtok->subword[(*j)++] = line[i - 1];
		else if (handle_sq(&line[i], &i, stk) || handle_dq(&line[i], &i, stk))
			break ;
		else if (handle_space_sep(&line[i], stk))
			break ;
		else if (handle_sep(&line[i], &i, j, g))
			break ;
		else if (line[i])
		{
			check_dollar(&line[i], stk, subtok);
			subtok->subword[(*j)++] = line[i++];
		}
	}
	return (i);
}

int	parse_word(char *line, t_global *g, t_tok_nd *nd)
{
	int			j;
	int			i;
	t_subtok	*subtok;

	i = 0;
	nd->paren_lvl = g->tok_stk.paren_lvl;
	while (line[i])
	{
		subtok = get_and_addback_subtok(&line[i], g, nd);
		j = ft_strlen(subtok->subword);
		i += parse_subword(&j, &line[i], g, nd);
		subtok->subword[j] = '\0';
		if (handle_space_sep(&line[i], &g->tok_stk) || is_sep(&line[i], nd))
			break ;
		j = 0;
	}
	return (i);
}

void	check_end_line(t_global *g)
{
	while (!is_end_line(&g->tok_stk))
	{
		if (is_operator_endline(&g->tok_stk))
			handle_incomplete_op(g);
		else if (g->tok_stk.state != NORMAL)
			handle_incomplete_quote(g);
		else if (g->tok_stk.backslash == 1)
			handle_incomplete_bs(g);
		else
			handle_incomplete_parenthesis(g);
	}
}

void	parsing_tokens(t_global *g)
{
	int			i;
	t_tok_stk	*stk;
	t_tok_nd	*nd;

	stk = &g->tok_stk;
	nd = stk->top;
	i = 0;
	while (g->rd.line[i])
	{
		while (handle_space_sep(&g->rd.line[i], stk)) // voir les autres ch a sauter en plus du space
			i++;
		nd = get_and_addback_nd(g);
		i += parse_word(&g->rd.line[i], g, nd);
	}
	check_end_line(g);
}
