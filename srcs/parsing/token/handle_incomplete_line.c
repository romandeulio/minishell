/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_incomplete_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:33:07 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 14:00:33 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	handle_incomplete_bs(t_global *g)
{
	char	*tmp;

	tmp = g->rd.full_line;
	g->rd.full_line = ft_strndup(tmp, ft_strlen(tmp) - 1);
	free(tmp);
	if (!g->rd.full_line)
		exit_free(g, "Malloc", -1, 1);
	free(g->rd.line);
	if (!g->rd.line)
	{
		free_and_reset_readline(g);
		free_and_reset_parsing(g);
		rl_clear_history();
		ft_putendl_fd("Exit", 1);
		exit(0);
	}
	g->rd.line = readline("> ");
	tmp = g->rd.full_line;
	g->rd.full_line = ft_strjoin(tmp, g->rd.line);
	free(tmp);
	if (!g->rd.full_line)
		exit_free(g, "Malloc", -1, 1);
	if (!g->rd.line[0])
		g->tok_stk.backslash = 0;
	parsing_tokens(g);
}

void	handle_incomplete_op(t_global *g)
{
	char	*tmp;

	free(g->rd.line);
	g->rd.line = readline("> ");
	if (!g->rd.line)
	{
		write_endline_error(g);
		return ;
	}
	tmp = g->rd.full_line;
	g->rd.full_line = ft_strjoin(tmp, g->rd.line);
	free(tmp);
	if (!g->rd.full_line)
		exit_free(g, "Malloc", -1, 1);
	parsing_tokens(g);
}

void	handle_incomplete_quote(t_global *g)
{
	char	*line_separator;

	free(g->rd.line);
	g->rd.line = readline("> ");
	if (!g->rd.line)
	{
		write_endline_error(g);
		return ;
	}
	line_separator = ft_strjoin(g->rd.full_line, "\n");
	if (!line_separator)
		exit_free(g, "Malloc", -1, 1);
	free(g->rd.full_line);
	g->rd.full_line = ft_strjoin(line_separator, g->rd.line);
	free(line_separator);
	if (!g->rd.full_line)
		exit_free(g, "Malloc", -1, 1);
	add_nl_last_nd(g);
	parsing_tokens(g);
}

void	handle_incomplete_paren2(t_global *g)
{
	char	*line_separator;
	char	*line_skip_sp;

	line_skip_sp = skip_spaces(g->rd.line);
	if (line_skip_sp[0] && !(line_skip_sp[0] == '(' || line_skip_sp[0] == ')'))
	{
		add_semicolon(g);
		line_separator = ft_strjoin(g->rd.full_line, "; ");
	}
	else
		line_separator = ft_strdup(g->rd.full_line);
	if (!line_separator)
		exit_free(g, "Malloc", -1, 1);
	free(g->rd.full_line);
	g->rd.full_line = ft_strjoin(line_separator, g->rd.line);
	free(line_separator);
	if (!g->rd.full_line)
		exit_free(g, "Malloc", -1, 1);
}

void	handle_incomplete_paren(t_global *g)
{
	free(g->rd.line);
	g->rd.line = readline("> ");
	if (!g->rd.line)
	{
		write_endline_error(g);
		return ;
	}
	handle_incomplete_paren2(g);
	parsing_tokens(g);
}
