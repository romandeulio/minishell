/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:35:48 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/19 22:23:28 by nicolasbrec      ###   ########.fr       */
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

int	handle_backslash(char **line, int i, char *word, t_tok_stk *stk)
{
	if ((*line)[i] == '\\')
	{
		stk->backslash = !stk->backslash;
		if ((*line)[i + 1])
		{
			printf("word[0] = %c\n", word[0]);
			word[0] = (*line)[i + 1];
			printf("word[0] = %c\n", word[0]);
			*line += 2;
			if (!(*line)[i])
				return (1);
			else
				return (0);
		}
		*line += 1;
		return (1);
	}
	return (0);
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
		if (handle_backslash(&line, i, &nd->word[i], stk))
		{
			//
			continue;
		}
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

void	parsing_token(char *line, t_global *g)
{
	int			i;
	int			j;
	t_tok_stk	*stk;
	t_tok_nd	*nd;

	stk = &g->tok_stk;
	nd = stk->top;
	i = 0;
	j = 0;
	nd = lstnew_nd_token(1000, g);
	while (line[i])
	{
		if (handle_backslach())
			//
		else if (handle_sq())
			//
		else if (handle_dq())
			//
		else if (handle_space())
			//
		else
			nd->word[j] = line[i];

	}
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
		while (g->rd.line[i] && g->rd.line[i] != ' ')
			i++;
		parsing_token(&g->rd.line[i]);
	}
}
