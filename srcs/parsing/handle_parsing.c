/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:16:39 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/21 13:27:24 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_backslash(char *line, int *i, t_tok_stk *stk)
{
	if (line[0] == '\\' && !stk->sq)
	{
		stk->backslash = 1;
		if (line[1])
		{
			(*i) += 2;
			stk->backslash = 0;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	handle_sq(char *line, int *i, t_tok_stk *stk)
{
	if (line[0] == '\'' && !stk->dq)
	{
		stk->sq = !stk->sq;
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_dq(char *line, int *i, t_tok_stk *stk)
{
	if (line[0] == '\"' && !stk->sq)
	{
		stk->dq = !stk->dq;
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_space_sep(char *line, t_tok_stk *stk)
{
	if (line[0] == ' ' && !stk->sq && !stk->dq)
    {
        stk->backslash = 0;
		return (1);
    }
	return (0);
}

int	handle_sep(char *line, int *i, t_global *g, t_tok_nd *nd)
{
	t_tok_stk	*stk;
	int			size_sep;

	stk = &g->tok_stk;
	nd->type = CMD;
	if (stk->sq || stk->dq)
		return (0);
	defined_type(line, nd);
	if (nd->type != CMD)
	{
		if (*i == 0)
		{
			size_sep = save_sep(line, nd);
            *i += size_sep;
			handle_parentheses(g, nd);
            return (1);
		}
		nd->type = CMD;
		return (1);
	}
	return (0);
}
