/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 01:08:40 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/19 21:59:33 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	sq_token_len(char *line)
{
	int	i;

	i = 0;
	// (pas obligatoire)
	// if (*line == '\'' && stk->sq == 1)
	// 	return(0);
	if (*line == '\'')
		line++;
	while (line[i] && line[i] != '\'')
		i++;
	return (i);
}

int	dq_token_len(char *line)
{
	int	i;

	i = 0;
	// (pas obligatoire)
	// if (*line == '\"' && stk->dq == 1)
	// 	return(0);
	if (*line == '\"')
		line++;
	while (line[i] && line[i] != '\"')
		i++;
	return (i);
}

int	word_token_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_word(&line[i]))
		i++;
	return (i);
}

int	token_len(char *line)
{
	if (is_parenthesis(line))
		return (1);
	else if (is_redir(line))
		return (is_redir(line));
	else if (is_operator(line))
		return (is_operator(line));
    else if (*line == ';')
        return (1);
	else if (*line == '\'')
		return (sq_token_len(line));
	else if (*line == '\"')
		return (dq_token_len(line));
	else
		return (word_token_len(line));
}
