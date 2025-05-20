/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:18:03 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/20 02:03:47 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	count_size_token(char *line, t_tok_stk *stk)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (count_backslash(&line[i], &i, stk))
			count++;
		else if (count_sq(&line[i], &i, stk) || count_dq(&line[i], &i, stk))
			continue ;
		else if (count_space_sep(&line[i], stk))
			break ;
		else if (count_sep(&line[i], &i, stk))
			break ;
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}
