/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definited_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 00:12:33 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/19 15:11:02 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	definited_type(char *line, t_tok_nd *nd)
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

void	definited_state(char *line, t_tok_nd *nd, t_tok_stk *stk)
{
	if (*line == '\'' || stk->sq)
		nd->state = SQ;
	else if (*line == '\"' || stk->dq)
		nd->state = DQ;
	else
		nd->state = NORMAL;
}
