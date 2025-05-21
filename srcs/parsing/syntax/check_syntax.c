/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:02:00 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/21 16:45:34 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int check_start_error(t_tok_nd *first, t_global *g)
{
    if (is_operator(first->type))
    {
        close_line(first->word, g);
        return (1) ;
    }
    return (0);
}

int check_middle_error(t_tok_nd *first, t_tok_nd *next, t_global *g)
{
    if (is_operator(first->type) && next && is_operator(next->type))
    {
        close_line(next->word, g);
        return (1);
    }
    else if (is_redir(first->type) && next && !is_cmd(next->type))
    {
        close_line(first->next->word, g);
        return (1);
    }
    else if (is_cmd(first->type) && next && next->type == PAREN_OPEN)
    {
        close_line(next->next->word, g);
        return (1);
    }
    else if (first->type == PAREN_CLOSE && next && is_cmd(next->type))
    {
        close_line(next->word, g);
        return (1);
    }
    return (0);
}


int check_end_error(t_tok_nd *first, t_global *g)
{
    if (is_operator(first->type))
    {
        close_line(first->word, g);
        return (1);
    }
    else if (is_redir(first->type))
    {
        close_line("newline", g);
        return (1);
    }
    return (0);
}

void	check_syntax(t_global *g)
{
	int			i;
	t_tok_stk	*stk;
	t_tok_nd	*first;
	t_tok_nd	*next;

	stk = &g->tok_stk;
	first = stk->top;
	i = 1;
	while (first)
	{
		next = first->next;
        if (i == 1 && check_start_error(first, g))
			break ;
		else if (check_middle_error(first, next, g))
            break ;
        else if (i == lstcount_nd_token(stk) && check_end_error(first, g))
            break ;
        i++;
		first = next;
	}
}
