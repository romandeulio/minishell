/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tok_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:15:23 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/26 12:59:07 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	handle_parentheses(t_global *g, t_tok_nd *nd)
{
	t_tok_stk	*stk;

	stk = &g->tok_stk;
	if (nd->type == PAREN_OPEN)
		stk->parenthesis++;
	else if (nd->type == PAREN_CLOSE)
		stk->parenthesis--;
	if (stk->parenthesis == -1)
	{
		write_syntax_error(nd->top);
		ft_exit(NULL, g);
	}
}

int	save_sep(char *line, t_tok_nd *nd)
{
	int			i;
	t_type		t;
	t_subtok	*subtok;

	subtok = lstget_last_nd_subtok(nd->top);
	t = nd->type;
	i = 0;
	if (t == AND || t == OR || t == HERE_DOC || t == APPEND)
	{
		subtok->subword[i] = line[i];
		subtok->subword[i + 1] = line[i + 1];
		i += 2;
	}
	else
	{
		subtok->subword[i] = line[i];
		i++;
	}
	// nd->word[i] = '\0' (si j'enleve verif le '\0' dans parsing_token)
	return (i);
}

void	check_dollar(char c, t_tok_stk *stk, t_tok_nd *nd)
{
	if (c == '$' && stk->state != SQ)
		nd->varenv = 1;
}

t_tok_nd	*get_nd(t_global *g)
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
	return (new);
}

// t_tok_nd	*get_nd(int size, char *line, t_global *g)
// {
// 	t_tok_stk	*stk;
// 	t_tok_nd	*last;
// 	t_tok_nd	*new;

// 	stk = &g->tok_stk;
// 	new = lstnew_nd_tok(g);
// 	last = lstget_last_nd_tok(stk);
// 	if (stk->sq || stk->dq || stk->backslash)
// 	{
// 		stk->backslash = 0;
// 		free(new->word);
// 		new->word = realloc_token(line, last, g);
// 		lstdel_last_nd_tok(stk);
// 	}
// 	return (new);
// }

// char	*realloc_token(char *line, t_tok_nd *last, t_global *g)
// {
// 	int			total_len;
// 	char		*new_word;
// 	t_tok_stk	*stk;

// 	stk = &g->tok_stk;
// 	total_len = count_size_token(line, stk) + ft_strlen(last->word);
// 	new_word = malloc(sizeof(char) * (total_len + 1));
// 	if (!new_word)
// 		ft_exit("Malloc", g);
// 	ft_strcpy(new_word, last->word);
// 	return (new_word);
// }
