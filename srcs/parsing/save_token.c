/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:01:20 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/19 00:22:28 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	save_word_quote_state(char *line, char *word, char separator)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != separator)
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	if (line[i] == separator)
		return (1);
	return (0);
}

void	save_word_normal_state(char *line, char *word)
{
	int	i;

	i = 0;
	while (line[i] && is_word(&line[i]))
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
}

void	save_separator(char *line, char *word, t_type t)
{
	int	i;

	i = 0;
	if (t == AND || t == OR || t == HERE_DOC || t == APPEND)
	{
		word[i] = line[i];
		word[i + 1] = line[i + 1];
		i += 2;
	}
	else
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
}
