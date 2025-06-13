/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:08:58 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:38:30 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	parse_subword(int *j, char *line, t_global *g, t_tok_nd *nd)
{
	int			i;
	t_tok_stk	*stk;
	t_subtok	*subtok;

	i = 0;
	stk = &g->tok_stk;
	subtok = lstget_last_nd_subtok(nd->top);
	while (line[i])
	{
		if (handle_backslash(&line[i], &i, stk))
			subtok->subword[(*j)++] = line[i - 1];
		else if (handle_sq(&line[i], &i, stk) || handle_dq(&line[i], &i, stk))
			break ;
		else if (handle_space_sep(&line[i], stk))
			break ;
		else if (handle_sep(&line[i], &i, j, g))
			break ;
		else if (line[i])
		{
			check_meta(&line[i], stk, subtok);
			subtok->subword[(*j)++] = line[i++];
		}
	}
	return (i);
}

int	parse_word(char *line, t_global *g, t_tok_nd *nd)
{
	int			j;
	int			i;
	t_subtok	*subtok;

	i = 0;
	nd->paren_lvl = g->tok_stk.paren_lvl;
	while (line[i])
	{
		subtok = get_and_addback_subtok(&line[i], g, nd);
		j = ft_strlen(subtok->subword);
		i += parse_subword(&j, &line[i], g, nd);
		subtok->subword[j] = '\0';
		if (handle_space_sep(&line[i], &g->tok_stk) || is_sep(&line[i], nd))
			break ;
		j = 0;
	}
	return (i);
}

void	check_end_line(t_global *g)
{
	while (!is_end_line(&g->tok_stk))
	{
		if (g->error_line || check_syntax(g, 0))
			return ;
		if (is_operator_endline(&g->tok_stk))
			handle_incomplete_op(g);
		else if (g->tok_stk.state != NORMAL)
			handle_incomplete_quote(g);
		else if (g->tok_stk.backslash == 1)
			handle_incomplete_bs(g);
		else
			handle_incomplete_paren(g);
	}
}

void	parsing_tokens(t_global *g)
{
	int			i;
	t_tok_stk	*stk;
	t_tok_nd	*nd;
	t_tok_nd	*last;

	if (!g->rd.line)
		return ;
	stk = &g->tok_stk;
	nd = stk->top;
	last = lstget_last_nd_tok(nd);
	i = 0;
	while (g->rd.line[i])
	{
		while (handle_space_sep(&g->rd.line[i], stk))
			i++;
		if (!g->rd.line[i])
			break ;
		nd = get_and_addback_nd(g);
		i += parse_word(&g->rd.line[i], g, nd);
	}
	check_heredoc(g, last);
	check_end_line(g);
}
