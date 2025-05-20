/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tok_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:15:23 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/20 17:58:34 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		write_error_syntax(nd->word);
		ft_exit(NULL, g);
	}
}

int	save_sep(char *line, t_tok_nd *nd)
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
	return (i);
}

void check_dollar(char c, t_tok_stk *stk, t_tok_nd *nd)
{
	if (c == '$' && !stk->sq)
		nd->varenv = 1;
}

t_tok_nd *get_nd(int size, char *line, t_global *g)
{
	t_tok_stk *stk;
	t_tok_nd *last;
    t_tok_nd *new;
	
	stk = &g->tok_stk;
    new = lstnew_nd_token(size, g);
	last = lstlast_nd(stk);
	if (last)
	{
		if ((last->state == SQ && stk->sq) || (last->state == DQ && stk->dq))
		{
            new->varenv = last->varenv;
            free(new->word);
			new->word = realloc_token(line, last, stk);
            printf("AVANT :\n");
            print_token(g);
            lstdel_last_nd(stk);
            printf("APRES :\n");
            print_token(g);
		}
	}
	return (new);
}

char *realloc_token(char *line, t_tok_nd *last, t_tok_stk *stk)
{
	int total_len;
	char *new_word;
	
	total_len = count_size_token(line, stk) + ft_strlen(last->word);
	new_word = malloc(sizeof(char) * (total_len + 1));
	ft_strcpy(new_word, last->word);
    return (new_word);
}
