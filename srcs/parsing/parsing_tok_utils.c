/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tok_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:15:23 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/20 13:45:39 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_parentheses(t_global *g, t_tok_nd *nd)
{
	t_tok_stk	*stk;

	stk = &g->tok_stk;
	if (nd->type == PAREN_OPEN)
		stk->parenthesis++;
	else if (nd->type == PAREN_CLOSE)
		stk->parenthesis--;
	if (stk->parenthesis == -1)
	{
		write_error_syntax(nd->word);
		ft_exit(NULL, g);
	}
}

int	save_sep(char *line, t_tok_nd *nd)
{
	int		i;
	t_type	t;

	t = nd->type;
	i = 0;
	if (t == AND || t == OR || t == HERE_DOC || t == APPEND)
	{
		nd->word[i] = line[i];
		nd->word[i + 1] = line[i + 1];
		i += 2;
	}
	else
	{
		nd->word[i] = line[i];
		i++;
	}
	nd->word[i] = '\0';
	return (i);
}

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
void check_dollar(char c, t_tok_stk *stk, t_tok_nd *nd)
{
	if (c == '$' && !stk->sq)
		nd->varenv = 1;
}
