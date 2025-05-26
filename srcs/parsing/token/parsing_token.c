/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:08:58 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/26 14:13:19 by nicolasbrec      ###   ########.fr       */
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

// int	parse_subword(int *j, char *line, t_global *g, t_tok_nd *nd)
// {
// 	int			i;
// 	t_tok_stk	*stk;

// 	i = 0;
// 	stk = &g->tok_stk;
// 	while (line[i])
// 	{
// 		if (handle_backslash(&line[i], &i, stk))
// 			nd->word[(*j)++] = line[i - 1];
// 		else if (handle_sq(&line[i], &i, stk) || handle_dq(&line[i], &i, stk))
// 			continue ;
// 		else if (handle_space_sep(&line[i], stk))
// 			break ;
// 		else if (handle_sep(&line[i], &i, g, nd))
// 			break ;
// 		else if (line[i])
// 		{
// 			check_dollar(*line, stk, nd);
// 			nd->word[(*j)++] = line[i++];
// 		}
// 	}
// 	return (i);
// }

// int	parse_token(char *line, t_global *g, t_tok_nd *nd)
// {
// 	int	j;
// 	int	i;

// 	j = ft_strlen(nd->word);
// 	i = parse_loop(&j, line, g, nd);
// 	// if (nd->type == CMD)
// 	nd->word[j] = '\0';

// 	return (i);
// }

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
		else if (handle_sep(&line[i], &i, g, nd))
			break ;
		else if (line[i])
		{
			check_dollar(*line, stk, nd);
			subtok->subword[(*j)++] = line[i++];
		}
	}
	return (i);
}

// t_subtok *get_subtok(int size, char *line, t_global *g)
// {
// 	t_subtok *new;
// 	t_subtok *last;

// 	new = lstnew_nd_subtok(size, g);

// }

void realloc_subword(char *line,  t_global *g, t_subtok *last)
{
	int size;
	int total_len;
	char *new_subword;
	t_tok_stk *stk;
	
	stk = &g->tok_stk;
	size = count_size_subword(line, stk);
	total_len = size + ft_strlen(last->subword);
	new_subword = malloc(sizeof(char) * (total_len + 1));
	if (!new_subword)
		ft_exit("Malloc", g); // Voir si il faut free de nouveaux trucs
	ft_strcpy(new_subword, last->subword);
	new_subword[size] = '\0';
	free(last->subword);
}

t_subtok *get_and_addback_subtok(char *line, t_global *g, t_tok_nd *nd)
{
	int size;
	t_subtok *last;
	t_tok_stk *stk;
	
	size = count_size_subword(line, &g->tok_stk);
	stk = &g->tok_stk;
	last = lstget_last_nd_subtok(nd->top);
	if (!nd->top || last->state != stk->state)
	{
		last = lstnew_nd_subtok(size, g);
		lstadd_back_subtok(&nd->top, last);
	}
	else
		realloc_subword(line, g, last);
	return (last);
}

int	parse_word(char *line, t_global *g, t_tok_nd *nd)
{
	int			j;
	int			i;
	t_subtok	*subtok;

	i = 0;
	while (line[i])
	{
		printf("Debut de boucle parse_word\n");
		subtok = get_and_addback_subtok(line, g, nd);
		// new = lstnew_nd_subtok(size, g); // Faire en sorte que ca prenne le dernier node si c'est le meme state. Et un nouveau si c'est pas le meme que le dernier node
		// lstadd_back_subtok(&nd->top, new);
		j = ft_strlen(subtok->subword); // 
		i += parse_subword(&j, line, g, nd);
		subtok->subword[j] = '\0';
		printf("Avant break\n");
		if (g->tok_stk.top->type != CMD || handle_space_sep(line, &g->tok_stk))
			break ;
		j = 0;
		printf("Apres break\n");
	}
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
		else if (g->tok_stk.state != NORMAL)
			handle_incomplete_quote(g);
		else
			handle_incomplete_parenthesis(g);
	}
	print_token(g);
}

t_tok_nd *get_and_addback_nd(t_global *g)
{
	t_tok_stk	*stk;
	t_tok_nd	*new;

	stk = &g->tok_stk;
	if (stk->state != NORMAL || stk->backslash)
	{
		stk->backslash = 0;
		new = lstget_last_nd_tok(stk->top);
	}
	else
		new = lstnew_nd_tok(g);
	lstadd_back_tok(stk, new);
	return (new);
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
		while (handle_space_sep(&g->rd.line[i], stk))
			i++;
		// nd = get_nd(g);
		// lstadd_back_tok(stk, nd);
		nd = get_and_addback_nd(g);
		printf("ici\n");
		i += parse_word(&g->rd.line[i], g, nd);
		printf("ici\n");
	}
	check_end_line(g);
}
