/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:33:07 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/21 15:58:49 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	handle_incomplete_bs(t_global *g)
{
	char	*tmp;
	char	*line_clean;
	char	*full_line;

	tmp = g->rd.line;
	g->rd.line = readline(">");
	line_clean = ft_strndup(tmp, ft_strlen(tmp) - 1);
	if (!line_clean)
		ft_exit("Malloc", g);
	free(tmp);
	full_line = ft_strjoin(line_clean, g->rd.line);
	if (!full_line)
	{
		free(line_clean);
		ft_exit("Malloc", g);
	}
	free(line_clean);
	if (!g->rd.line[0])
		g->tok_stk.backslash = 0;
	parsing_tokens(g);
	free(g->rd.line);
	g->rd.line = full_line;
}

void	handle_incomplete_op(t_global *g)
{
	char	*tmp;
	char	*full_line;

	tmp = g->rd.line;
	g->rd.line = readline(">");
	full_line = ft_strjoin(tmp, g->rd.line);
	if (!full_line)
		ft_exit("Malloc", g);
	free(tmp);
	parsing_tokens(g);
	free(g->rd.line);
	g->rd.line = full_line;
}

void	handle_incomplete_quote(t_global *g)
{
	char	*tmp;
	char	*line_separator;
	char	*full_line;

	tmp = g->rd.line;
	g->rd.line = readline(">");
	line_separator = ft_strjoin(tmp, "\n");
	if (!line_separator)
		ft_exit("Malloc", g);
	free(tmp);
	full_line = ft_strjoin(line_separator, g->rd.line);
	if (!full_line)
	{
		free(line_separator);
		ft_exit("Malloc", g);
	}
	free(line_separator);
	add_nl_last_nd(g);
	parsing_tokens(g);
	free(g->rd.line);
	g->rd.line = full_line;
}

void	handle_incomplete_parenthesis(t_global *g)
{
	char	*tmp;
	char	*line_separator;
	char	*full_line;

	add_semicolon(g);
	tmp = g->rd.line;
	g->rd.line = readline(">");
	line_separator = ft_strjoin(tmp, "; ");
	if (!line_separator)
		ft_exit("Malloc", g);
	free(tmp);
	full_line = ft_strjoin(line_separator, g->rd.line);
	if (!full_line)
	{
		free(line_separator);
		ft_exit("Malloc", g);
	}
	free(line_separator);
	parsing_tokens(g);
	free(g->rd.line);
	g->rd.line = full_line;
}
