/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_incomplete_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:33:07 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/29 16:14:52 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// void	handle_incomplete_bs(t_global *g)
// {
// 	char	*tmp;
// 	char	*line_clean;
// 	char	*full_line;

// 	tmp = g->rd.line;
// 	g->rd.line = readline(">");
// 	line_clean = ft_strndup(tmp, ft_strlen(tmp) - 1);
// 	if (!line_clean)
// 		ft_exit("Malloc", g);
// 	free(tmp);
// 	full_line = ft_strjoin(line_clean, g->rd.line);
// 	free(line_clean);
// 	if (!full_line)
// 		ft_exit("Malloc", g);
// 	if (!g->rd.line[0])
// 		g->tok_stk.backslash = 0;
// 	parsing_tokens(g);
// 	free(g->rd.line);
// 	g->rd.line = full_line;
// }

void	handle_incomplete_bs(t_global *g)
{
	char *tmp;

	tmp = g->rd.full_line;
	g->rd.full_line = ft_strndup(tmp, ft_strlen(tmp) - 1);
	free(tmp);
	if (!g->rd.full_line)
		ft_exit(g, "Malloc", -1, 1);
	free(g->rd.line);
	g->rd.line = readline(">");
	tmp = g->rd.full_line;
	g->rd.full_line = ft_strjoin(tmp, g->rd.line);
	free(tmp);
	if (!g->rd.full_line)
		ft_exit(g, "Malloc", -1, 1);
	if (!g->rd.line[0])
		g->tok_stk.backslash = 0;
	parsing_tokens(g);
}

void	handle_incomplete_op(t_global *g)
{
	char *tmp;

	free(g->rd.line);
	g->rd.line = readline(">");
	tmp = g->rd.full_line;
	g->rd.full_line = ft_strjoin(tmp, g->rd.line);
	free(tmp);
	if (!g->rd.full_line)
		ft_exit(g, "Malloc", -1, 1);
	parsing_tokens(g);
}

void	handle_incomplete_quote(t_global *g)
{
	char	*line_separator;

	free(g->rd.line);
	g->rd.line = readline(">");
	line_separator = ft_strjoin(g->rd.full_line, "\n");
	if (!line_separator)
		ft_exit(g, "Malloc", -1, 1);
	free(g->rd.full_line);
	g->rd.full_line = ft_strjoin(line_separator, g->rd.line);
	if (!g->rd.full_line)
		ft_exit(g, "Malloc", -1, 1);
	add_nl_last_nd(g);
	parsing_tokens(g);
}

void	handle_incomplete_parenthesis(t_global *g)
{
	char	*line_separator;

	add_semicolon(g);
	free(g->rd.line);
	g->rd.line = readline(">");
	line_separator = ft_strjoin(g->rd.full_line, "; ");
	if (!line_separator)
		ft_exit(g, "Malloc", -1, 1);
	free(g->rd.full_line);
	g->rd.full_line = ft_strjoin(line_separator, g->rd.line);
	if (!g->rd.full_line)
		ft_exit(g, "Malloc", -1, 1);
	parsing_tokens(g);
}
