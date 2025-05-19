/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:00:24 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/19 22:01:08 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parsing_sq_state(char *line, t_tok_stk *stk, t_tok_nd *nd)
{
	int	i;

	i = 0;
	stk->sq = 1;
	// (pas obligatoire)
	// if (line[i] == '\'' && stk->sq == 1)
	// 	return(0);
	if (line[i] == '\'')
		line++;
	while (line[i] && line[i] != '\'')
	{
		nd->word[i] = line[i];
		i++;
	}
	nd->word[i] = '\0';
	if (line[i] == '\'')
	{
		stk->sq = 0;
		return (2);
	}
	return (1);
}

int	handle_backslash(char **line, int i, char *word, t_tok_stk *stk)
{
	if ((*line)[i] == '\\')
	{
		stk->backslash = !stk->backslash;
		if ((*line)[i + 1])
		{
			printf("word[0] = %c\n", word[0]);
			word[0] = (*line)[i + 1];
			printf("word[0] = %c\n", word[0]);
			*line += 2;
			if (!(*line)[i])
				return (1);
			else
				return (0);
		}
		*line += 1;
		return (1);
	}
	return (0);
}

int	parsing_dq_state(char *line, t_tok_stk *stk, t_tok_nd *nd)
{
	int	i;

	i = 0;
	stk->dq = 1;
	// (pas obligatoire)
	// if (line[i] == '\"' && stk->dq == 1)
	// 	line++;
	if (line[i] == '\"')
		line++;
	while (line[i] && line[i] != '\"')
	{
		if (handle_backslash(&line, i, &nd->word[i], stk))
		{
			//
			continue;
		}
		if (line[i] == '$')
			nd->varenv = 1;
		nd->word[i] = line[i];
		i++;
	}
	nd->word[i] = '\0';
	if (line[i] == '\"')
	{
		stk->dq = 0;
		printf("stk->dq = %d\n", stk->dq);
		return (2);
	}
	return (1);
}

int	parsing_normal_state(char *line, t_tok_nd *nd)
{
	int	i;

	i = 0;
	while (line[i] && is_word(&line[i]))
	{
		nd->word[i] = line[i];
		i++;
	}
	nd->word[i] = '\0';
	return (0);
}

int	parsing_separator(char *line, t_tok_nd *nd)
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
	return (0);
}

int	incr_until_next_tok(char *line, t_tok_stk *stk)
{
	if (!*line)
		return (0);
	else if (*line == ' ')
		return (1);
	else if (*line == '\'' && stk->sq == 1)
	{
		stk->sq = !stk->sq;
		return (1);
	}
	else if (*line == '\"' && stk->dq == 1)
	{
		stk->dq = !stk->dq;
		return (1);
	}
	else
		return (0);
}
