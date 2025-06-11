/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:18:03 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/10 11:48:38 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	count_size_sep(char *line, int *sep)
{
	if (*line == ';')
		(*sep)++;
	else if (!ft_strncmp(line, "||", 2))
		(*sep) += 2;
	else if (!ft_strncmp(line, "&&", 2))
		(*sep) += 2;
	else if (*line == '|')
		(*sep)++;
	else if (!ft_strncmp(line, ">>", 2))
		(*sep) += 2;
	else if (!ft_strncmp(line, "<<", 2))
		(*sep) += 2;
	else if (*line == '>')
		(*sep)++;
	else if (*line == '<')
		(*sep)++;
	else if (*line == ')')
		(*sep)++;
	else if (*line == '(')
		(*sep)++;
}

int	count_sep(char *line, int *i, int *count, t_tok_stk *stk)
{
	int	sep;

	sep = 0;
	if (stk->state != NORMAL || stk->backslash)
		return (0);
	count_size_sep(line, &sep);
	if (sep)
	{
		if (*i == 0)
		{
			*i += sep;
			*count += sep;
		}
		return (1);
	}
	return (0);
}

int	count_sq(char *line, int *i, t_tok_stk *stk)
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

int	count_dq(char *line, int *i, t_tok_stk *stk)
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

int	count_size_subword(char *line, t_tok_stk *original_stk)
{
	int			i;
	int			count;
	t_tok_stk	stk;

	i = 0;
	count = 0;
	ft_memcpy(&stk, original_stk, sizeof(t_tok_stk));
	while (line[i])
	{
		if (handle_backslash(&line[i], &i, &stk))
			count++;
		else if (count_sq(&line[i], &i, &stk) || count_dq(&line[i], &i, &stk))
			break ;
		else if (handle_space_sep(&line[i], &stk))
			break ;
		else if (count_sep(&line[i], &i, &count, &stk))
			break ;
		else if (line[i])
		{
			i++;
			count++;
		}
	}
	return (count);
}
