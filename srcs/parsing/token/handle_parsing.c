/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:16:39 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/27 16:20:25 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	handle_backslash(char *line, int *i, t_tok_stk *stk)
{
	if (line[0] == '\\' && stk->state != SQ)
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
	if (line[0] == '\'' && stk->state != DQ)
	{
		if (stk->state == SQ)
			stk->state = NORMAL;
		else
			stk->state = SQ;
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_dq(char *line, int *i, t_tok_stk *stk)
{
	if (line[0] == '\"' && stk->state != SQ)
	{
		if (stk->state == DQ)
			stk->state = NORMAL;
		else
			stk->state = DQ;
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_space_sep(char *line, t_tok_stk *stk)
{
	if (line[0] == ' ' && stk->state == NORMAL)
	{
		stk->backslash = 0;
		return (1);
	}
	return (0);
}

int	handle_sep(char *line, int *i, int *j, t_global *g)
{
	t_tok_stk	*stk;
	t_tok_nd	*nd;
	int			size_sep;

	nd = lstget_last_nd_tok(g->tok_stk.top);
	stk = &g->tok_stk;
	nd->type = CMD;
	if (stk->state != NORMAL)
		return (0);
	defined_type(line, nd);
	if (nd->type != CMD)
	{
		if (*i == 0)
		{
			size_sep = save_sep(line, nd);
			*i += size_sep;
			*j += size_sep;
			handle_parentheses(g, nd);
			return (1);
		}
		nd->type = CMD;
		return (1);
	}
	return (0);
}
