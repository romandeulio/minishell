/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:21:59 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/19 16:23:53 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int lstcount_node_token(t_tok_stk *stk)
{
	int count;
	t_tok_nd *nd;

	count = 0;
	nd = stk->top;
	while (nd)
	{
		nd = nd->next;
		count++;
	}
	return (count);
}

void	print_token(t_global *g)
{
	int i;
	int size;
	t_tok_stk	*stk;
	t_tok_nd	*nd;
	const char *type_name[] = {"CMD", "PAREN_OPEN", "PAREN_CLOSE", "IN_REDIR", 
		"OUT_REDIR", "HERE_DOC", "APPEND", "PIPE", "AND", "OR", "SEMICOLON"};
	const char *state_name[] = {"NORMAL", "SQ", "DQ"};

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
		printf("state = %s\n", state_name[nd->state]);
		nd = nd->next;
		printf("_______________\n");
	}
}

int is_end_line(t_tok_stk *stk)
{
	if (stk->parenthese == 0 && stk->sq == 0 && stk->dq == 0 && stk->backslash == 0)
		return (1);
	return (0);
}

void add_semicolon(t_global *g)
{
	t_tok_nd *nd;

	nd = lstnew_nd_token(1, g);
	nd->word[0] = ';';
	nd->word[1] = '\0';
	lstadd_back_token(&g->tok_stk, nd);
}

void	parsing(t_global *g)
{
	char *tmp;
	char *line_semicolon;
	char *full_line;
	
	parsing_token(g);
	while (!is_end_line(&g->tok_stk))
	{
		if (g->tok_stk.backslash == 1)
		{
			// nouvelle ligne mais pas nouvelle cmd
		}
		else
		{
			add_semicolon(g);
			tmp = g->rd.line;
			g->rd.line = readline(">");
			line_semicolon = ft_strjoin(tmp, "; ");
			free(tmp);
			full_line = ft_strjoin(line_semicolon, g->rd.line);
			free(line_semicolon);
			parsing_token(g);
			free(g->rd.line);
			g->rd.line = full_line;
		}
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
