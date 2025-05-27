/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tok_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:15:23 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/27 15:55:06 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	handle_parentheses(t_global *g, t_tok_nd *nd)
{
	t_tok_stk	*stk;

	stk = &g->tok_stk;
	if (nd->type == PAREN_OPEN)
		stk->paren_lvl++;
	else if (nd->type == PAREN_CLOSE)
		stk->paren_lvl--;
	if (stk->paren_lvl == -1)
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
	return (i);
}

void realloc_subword(char *line,  t_global *g, t_subtok *last)
{
	int size;
	int total_len;
	char *new_subword;
	t_tok_stk *stk;
	
	stk = &g->tok_stk;
	size = ft_strlen(last->subword);
	total_len = size + count_size_subword(line, stk);
	new_subword = malloc(sizeof(char) * (total_len + 1));
	if (!new_subword)
		ft_exit("Malloc", g); // Voir si il faut free de nouveaux trucs
	ft_strcpy(new_subword, last->subword);
	new_subword[size] = '\0';
	free(last->subword);
	last->subword = new_subword;
}

t_subtok *get_and_addback_subtok(char *line, t_global *g, t_tok_nd *nd)
{
	int size;
	t_subtok *last;
	t_tok_stk *stk;
	
	size = count_size_subword(line, &g->tok_stk);
	stk = &g->tok_stk;
	last = lstget_last_nd_subtok(nd->top);
	if (!nd->top || (last->state != stk->state && last->subword[0]))
	{
		last = lstnew_nd_subtok(size, g);
		lstadd_back_subtok(&nd->top, last);
	}
	else
	{
		realloc_subword(line, g, last);
		last->state = stk->state;
	}
	return (last);
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
	{
		new = lstnew_nd_tok(g);
		lstadd_back_tok(stk, new);
	}
	return (new);
}
