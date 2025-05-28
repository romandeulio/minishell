/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tok_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:18:11 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/28 13:28:49 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int is_sep(char *line, t_tok_nd *nd)
{
	if (nd->type != CMD)
		return (1);
	if (*line == ';')
		return (1);
	else if (!ft_strncmp(line, "||", 2))
		return (1);
	else if (!ft_strncmp(line, "&&", 2))
		return (1);
	else if (*line == '|')
		return (1);
	else if (!ft_strncmp(line, ">>", 2))
		return (1);
	else if (!ft_strncmp(line, "<<", 2))
		return (1);
	else if (*line == '>')
		return (1);
	else if (*line == '<')
		return (1);
	else if (*line == ')')
		return (1);
	else if (*line == '(')
		return (1);
	else
		return (0);
}

void check_dollar(char *line, t_tok_stk *stk, t_subtok *subtok)
{
	if (line[0] == '$' && stk->state != SQ)
		subtok->varenv = 1;
}
