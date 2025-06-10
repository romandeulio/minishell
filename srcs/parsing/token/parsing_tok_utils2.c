/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tok_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:18:11 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/10 11:48:25 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_sep(char *line, t_tok_nd *nd)
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

void	check_meta(char *line, t_tok_stk *stk, t_subtok *subtok)
{
	if (line[0] == '$' && stk->state != SQ)
		subtok->varenv = 1;
	else if (line[0] == '*' && stk->state == NORMAL)
		subtok->wildcard = 1;
}
