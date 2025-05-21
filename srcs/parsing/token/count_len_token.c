/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:18:03 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/21 15:58:43 by nicolasbrec      ###   ########.fr       */
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
	if (stk->sq || stk->dq || stk->backslash)
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

int	count_size_token(char *line, t_tok_stk *original_stk)
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
		else if (handle_sq(&line[i], &i, &stk) || handle_dq(&line[i], &i, &stk))
			continue ;
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
