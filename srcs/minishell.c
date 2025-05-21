/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:21:59 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/21 16:46:01 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token(t_global *g)
{
	int			i;
	int			size;
	t_tok_stk	*stk;
	t_tok_nd	*nd;
	const char	*type_name[] = {"CMD", "PAREN_OPEN", "PAREN_CLOSE", "IN_REDIR",
			"OUT_REDIR", "HERE_DOC", "APPEND", "PIPE", "AND", "OR",
			"SEMICOLON"};

	size = lstcount_nd_token(&g->tok_stk);
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
		printf("_______________\n");
	}
}

void	parsing(t_global *g)
{
	parsing_tokens(g);
	check_syntax(g);
	parsing_ast(g);
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
			// if (!g->error_line)
			// exec_cmd(g);
		}
		free_and_reset_readline(g);
		free_and_reset_parsing(g);
		g->error_line = 0;
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
