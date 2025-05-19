/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 01:00:59 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/19 22:02:38 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_parenthesis(char *s)
{
	if (*s == '(' || *s == ')')
		return (1);
	return (0);
}

int	is_redir(char *s)
{
	if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
		return (2);
	if (*s == '<' || *s == '>')
		return (1);
	return (0);
}

int	is_operator(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || !ft_strncmp(s, "||", 2))
		return (2);
	if (*s == '|')
		return (1);
	return (0);
}

int	is_word(char *s)
{
	if (!is_redir(s) && !is_operator(s) && !is_parenthesis(s) && *s != ' '
		&& *s != '\'' && *s != '\"' && *s != ';')
		return (1);
	return (0);
}