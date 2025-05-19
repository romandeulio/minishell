/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:35:48 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/19 16:10:50 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Erreur de parsing a detecter :
// (TOKEN) Quote jamais refermer (pas obligatoire).
// (AST) Un operateur logique au debut, a la fin,
//	ou plusieurs consequitifs. (a gerer dans l'arbe AST)
// (AST) Redirection sans cmd (mot autre qu'un separateur) qui suit la redirection
// (AST) Parenthese non fermante ou parenthese fermante sans l'avoir ouvrir
// (AST) Deux cmd d'affiler (compter aussi les cmd entre parentheses)


// int	handle_backslash(char *line, t_tok_stk *stk)
// {
// 	if (line[0] == '\\')
// 	{
// 		stk->backslash = !stk->backslash;
// 		if (!line[1])
// 			return ()
// 	}
// }

int	parsing_sq_state(char *line, t_tok_stk *stk, t_tok_nd *nd)
{
	int	i;

	i = 0;
	stk->sq = 1;
	// (pas obligatoire)
	// if (line[i] == '\'' && stk->sq == 1)
	// 	return(0);
	if (line[i] == '\'')
		line++;
	while (line[i] && line[i] != '\'')
	{
		nd->word[i] = line[i];
		i++;
	}
	nd->word[i] = '\0';
	if (line[i] == '\'')
	{
		stk->sq = 0;
		return (2);
	}
	return (1);
}

int	parsing_dq_state(char *line, t_tok_stk *stk, t_tok_nd *nd)
{
	int	i;

	i = 0;
	stk->dq = 1;
	// (pas obligatoire)
	// if (line[i] == '\"' && stk->dq == 1)
	// 	line++;
	if (line[i] == '\"')
		line++;
	while (line[i] && line[i] != '\"')
	{
		// handle_backslash(&line[i], nd->word);
		if (line[i] == '$')
			nd->varenv = 1;
		nd->word[i] = line[i];
		i++;
	}
	nd->word[i] = '\0';
	if (line[i] == '\"')
	{
		stk->dq = 0;
		printf("stk->dq = %d\n", stk->dq);
		return (2);
	}
	return (1);
}

int	parsing_normal_state(char *line, t_tok_nd *nd)
{
	int	i;

	i = 0;
	while (line[i] && is_word(&line[i]))
	{
		nd->word[i] = line[i];
		i++;
	}
	nd->word[i] = '\0';
	return (0);
}

int	parsing_separator(char *line, t_tok_nd *nd)
{
	int		i;
	t_type	t;

	t = nd->type;
	i = 0;
	if (t == AND || t == OR || t == HERE_DOC || t == APPEND)
	{
		nd->word[i] = line[i];
		nd->word[i + 1] = line[i + 1];
		i += 2;
	}
	else
	{
		nd->word[i] = line[i];
		i++;
	}
	nd->word[i] = '\0';
	return (0);
}

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

int	incr_until_next_tok(char *line, t_tok_stk *stk)
{
	if (!*line)
		return (0);
	else if (*line == ' ')
		return (1);
	else if (*line == '\'' && stk->sq == 1)
	{
		stk->sq = !stk->sq;
		return (1);
	}
	else if (*line == '\"' && stk->dq == 1)
	{
		stk->dq = !stk->dq;
		return (1);
	}
	else
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
		nd = lstnew_nd_token(size, g);
		definited_type(&g->rd.line[i], nd);
		definited_state(&g->rd.line[i], nd, stk);
		handle_parenthese(g, nd);
		i += parsing_token2(&g->rd.line[i], stk, nd);
		lstadd_back_token(stk, nd);
		i += size;
	}
}
