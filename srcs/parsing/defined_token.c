/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:04:34 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/20 16:05:15 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	defined_type(char *line, t_tok_nd *nd)
{
	if (*line == ';')
		nd->type = SEMICOLON;
	else if (!ft_strncmp(line, "||", 2))
		nd->type = OR;
	else if (!ft_strncmp(line, "&&", 2))
		nd->type = AND;
	else if (*line == '|')
		nd->type = PIPE;
	else if (!ft_strncmp(line, ">>", 2))
		nd->type = APPEND;
	else if (!ft_strncmp(line, "<<", 2))
		nd->type = HERE_DOC;
	else if (*line == '>')
		nd->type = OUT_REDIR;
	else if (*line == '<')
		nd->type = IN_REDIR;
	else if (*line == ')')
		nd->type = PAREN_CLOSE;
	else if (*line == '(')
		nd->type = PAREN_OPEN;
	else
		nd->type = CMD;
}

void	defined_state(t_tok_stk *stk, t_tok_nd *nd)
{
	if (stk->sq == 1)
		nd->state = SQ;
	else if (stk->dq == 1)
		nd->state = DQ;
	else
		nd->state = NORMAL;
}
