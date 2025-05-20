/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len_token2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:18:03 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/20 02:03:51 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_backslash(char *line, int *i, t_tok_stk *stk)
{
	if (*line == '\\' && !stk->sq)
	{
		if (*(line + 1))
		{
			(*i) += 2;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	count_sq(char *line, int *i, t_tok_stk *stk)
{
	if (*line == '\'' && !stk->dq && !stk->backslash)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	count_dq(char *line, int *i, t_tok_stk *stk)
{
	if (*line == '\"' && !stk->sq && !stk->backslash)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	count_space_sep(char *line, t_tok_stk *stk)
{
	if (*line == ' ' && !stk->sq && !stk->dq && !stk->backslash)
		return (1);
	return (0);
}

int	count_sep(char *line, int *i, t_tok_stk *stk)
{
	int	sep;

	sep = 0;
	if (stk->sq || stk->dq || stk->backslash)
		return (0);
	count_size_sep(line, &sep);
	if (sep)
	{
		if (*i == 0)
			*i += sep;
		return (1);
	}
	return (0);
}
