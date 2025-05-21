/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:21:59 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/21 14:18:04 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token(t_global *g)
{
	int i;
	int size;
	t_tok_stk	*stk;
	t_tok_nd	*nd;
	const char *type_name[] = {"CMD", "PAREN_OPEN", "PAREN_CLOSE", "IN_REDIR", 
		"OUT_REDIR", "HERE_DOC", "APPEND", "PIPE", "AND", "OR", "SEMICOLON"};

	size = lstcount_node_token(&g->tok_stk);
	i = 1;
	stk = &g->tok_stk;
	nd = stk->top;
	printf("_______________\n");
	while (nd)
	{
		printf("Word %d/%d :\n", i++, size);
		printf("word = {%s}\n", nd->word);
		printf("type = %s\n", type_name[nd->type]);
		printf("varenv = %d\n", nd->varenv);
		nd = nd->next;
		printf("nd = %p\n", nd);
		printf("_______________\n");
	}
}

int is_operator_endline(t_tok_stk *stk)
{
	t_type type;

	type = lstget_last_nd(stk)->type;
	if (type == PIPE || type == AND || type == OR)
		return (1);
	return (0);
}

void	parsing(t_global *g)
{	
	parsing_tokens(g);
	while (!is_end_line(&g->tok_stk))
	{
		if (g->tok_stk.backslash == 1)
			handle_incomplete_bs(g);
		else if (is_operator_endline(&g->tok_stk))
			handle_incomplete_op(g);
		else if (g->tok_stk.dq || g->tok_stk.sq)
			handle_incomplete_quote(g);
		else
			handle_incomplete_parenthesis(g);
	}
	print_token(g);
}

void	minishell(t_global *g)
{
	while (1)
	{
		g->rd.line = readline(get_cur_dir(g));
		if (!g->rd.line)
			ft_exit(NULL, g);
		else
		{
			parsing(g);
			check_and_add_history(g->rd.line);
		}
		free_and_reset_readline(g);
		free_and_reset_parsing(g);
	}
}

int	main(int ac, char **av, char **env)
{
	t_global	g;

	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("Usage: ./minishell", 2);
		return (1);
	}
	ft_bzero(&g, sizeof(t_global));
	g.env = env;
	minishell(&g);
	return (0);
}
