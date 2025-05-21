/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:02:37 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/21 16:03:01 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_operator(t_type t)
{
	if (t == PIPE || t == AND || t == OR || t == SEMICOLON)
		return (1);
	return (0);
}

int	is_redir(t_type t)
{
	if (t == HERE_DOC || t == APPEND || t == IN_REDIR || t == OUT_REDIR)
		return (1);
	return (0);
}

int is_parenthesis(t_type t)
{
	if (t == PAREN_OPEN || t == PAREN_CLOSE)
		return (1);
	return (0);
}

int is_cmd(t_type t)
{
	if (!is_operator(t) && !is_redir(t) && !is_parenthesis(t))
		return (1);
	return (0);
}
