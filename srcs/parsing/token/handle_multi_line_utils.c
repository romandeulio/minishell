/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:58:12 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:38:48 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_operator_endline(t_tok_stk *stk)
{
	t_tok_nd	*nd;
	t_type		type;

	nd = lstget_last_nd_tok(stk->top);
	if (!nd)
		return (0);
	type = nd->type;
	return (is_operator(type) && !is_weak_op(type));
}

int	is_end_line(t_tok_stk *stk)
{
	if (stk->paren_lvl <= 0 && stk->state == NORMAL && stk->backslash == 0
		&& !is_operator_endline(stk))
		return (1);
	return (0);
}

char	*skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] == ' ')
		i++;
	return (&str[i]);
}

void	add_semicolon(t_global *g)
{
	t_tok_nd	*nd;

	nd = lstnew_nd_tok(g);
	nd->type = SEMICOLON;
	nd->paren_lvl = g->tok_stk.paren_lvl;
	nd->top = lstnew_nd_subtok(1, g);
	nd->top->subword[0] = ';';
	nd->top->subword[1] = '\0';
	nd->top->state = NORMAL;
	lstadd_back_tok(&g->tok_stk, nd);
}

void	add_nl_last_nd(t_global *g)
{
	t_tok_nd	*last_nd;
	t_subtok	*last_subtok;
	char		*new;

	last_nd = lstget_last_nd_tok(g->tok_stk.top);
	if (!last_nd)
		return ;
	last_subtok = lstget_last_nd_subtok(last_nd->top);
	if (!last_subtok)
		return ;
	new = ft_strjoin(last_subtok->subword, "\n");
	if (!new)
		exit_free(g, "Malloc", -1, 1);
	free(last_subtok->subword);
	last_subtok->subword = new;
}
