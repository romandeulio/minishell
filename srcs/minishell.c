/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:21:59 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/26 13:56:57 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token(t_global *g)
{
	int			i;
	int			j;
	int			size;
	t_tok_stk	*stk;
	t_tok_nd	*nd;
	t_subtok	*subtok;
	const char	*type_name[] = {"CMD", "PAREN_OPEN", "PAREN_CLOSE", "IN_REDIR",
			"OUT_REDIR", "HERE_DOC", "APPEND", "PIPE", "AND", "OR",
			"SEMICOLON"};

	size = lstcount_nd_tok(&g->tok_stk);
	i = 1;
	stk = &g->tok_stk;
	nd = stk->top;
	printf("_______________\n");
	while (nd)
	{
		j = 1;
		subtok = nd->top;
		printf("Word %d/%d :\n", i++, size);
		while (subtok)
		{
			printf("subword %d = {%s}", j++, subtok->subword);
			if (i > 2)
				printf(" | ");
			subtok = subtok->next;
		}
		printf("\n");
		printf("type = %s\n", type_name[nd->type]);
		printf("varenv = %d\n", nd->varenv);
		nd = nd->next;
		printf("_______________\n");
	}
}

// int	get_priority_value(t_tok_nd *nd, int paren_lvl)
// {
// 	int	value;

// 	value = 0;
// 	if (nd->type == PIPE)
// 		value = 4;
// 	else if (nd->type == AND)
// 		value = 3;
// 	else if (nd->type == OR)
// 		value = 2;
// 	else if (nd->type == SEMICOLON)
// 		value = 1;
// 	value = value + (4 * paren_lvl);
// 	return (value);
// }

// t_tok_nd	*lstget_nd_index(t_tok_nd *cur, int index)
// {
// 	int	i;

// 	if (index < 0)
// 		return (NULL);
// 	i = 0;
// 	while (cur)
// 	{
// 		if (i == index)
// 			return (cur);
// 		cur = cur->next;
// 		i++;
// 	}
// 	return (NULL);
// }

// int	lstget_idx_nd(t_tok_nd *cur, t_tok_nd *target)
// {
// 	int	i;

// 	i = 0;
// 	while (cur)
// 	{
// 		if (cur == target)
// 			return (i);
// 		cur = cur->next;
// 		i++;
// 	}
// 	return (-1);
// }

// void	choice_params_ast(t_global *g, t_tok_nd *nd, t_parse_ast *pa_ast)
// {
// 	t_parse_ast	*new_pa_ast;
// 	int			new_start;
// 	int			tmp_end;

// 	new_start = lstget_idx_nd(g->tok_stk.top, nd);
// 	tmp_end = pa_ast->end;
// 	if (pa_ast->dir == 1)
// 	{
// 		pa_ast->end = pa_ast->start;
// 		ast_recursive(g, ft_memcpy(new_pa_ast, pa_ast, sizeof(t_parse_ast)));
// 		pa_ast->end = tmp_end;
// 		ast_recursive(g, ft_memcpy(new_pa_ast, pa_ast, sizeof(t_parse_ast)));
// 	}
// 	else
// 	{
// 		ast_recursive(g, ft_memcpy(new_pa_ast, pa_ast, sizeof(t_parse_ast)));
// 		pa_ast->end = pa_ast->start;
// 		ast_recursive(g, ft_memcpy(new_pa_ast, pa_ast, sizeof(t_parse_ast)));
// 	}
// }

// t_ast *astcreate_nd(t_global *g, t_tok_nd *nd, t_parse_ast *pa_ast)
// {
// 	t_ast *new;

// 	new = malloc(sizeof(t_ast));
// 	if (!new)
// 		ft_exit("Malloc", g); // verif si il faut liberer des trucs en
//			+ a cette etape
// 	new->type = nd->type;
// 	new->subshell = pa_ast->paren_lvl;
// 	if (new->type == CMD)
// 	{
// 		new->cmd = // Continuer ici
// 	}
// 	else
// 	{
// 		new->cmd = NULL;

// 	}
// }

// void fill_ast(t_global *g, t_tok_nd *nd, t_parse_ast *pa_ast)
// {

// }

// void	ast_recursive(t_global *g, void *cp_pa_ast)
// {
// 	t_parse_ast	*pa_ast;
// 	int			prio_min;
// 	t_tok_nd	*nd_min_prio;
// 	int			cur_i;
// 	t_tok_nd	*cur_nd;

// 	if (/*condition d'arret*/)
// 		return ;
// 	pa_ast = (t_parse_ast *)cp_pa_ast;
// 	prio_min = 0;
// 	cur_i = pa_ast->start;
// 	while (pa_ast->start != pa_ast->end)
// 	{
// 		cur_nd = lstget_nd_idx(g->tok_stk.top, cur_i);
// 		if (cur_nd->type == PAREN_OPEN)
// 			pa_ast->paren_lvl++;
// 		else if (cur_nd->type == PAREN_CLOSE)
// 			pa_ast->paren_lvl--;
// 		if (prio_min >= get_priority_value(cur_nd, pa_ast->paren_lvl))
// 			nd_min_prio = cur_nd;
// 		cur_i += pa_ast->dir;
// 	}
// 	choice_params_ast(g, nd_min_prio, pa_ast);
// }

// void	parsing_ast(t_global *g)
// {
// 	t_ast *ast;
// 	t_parse_ast	parse_ast;

// 	parse_ast.start = 0;
// 	parse_ast.end = lstcount_nd_tok(&g->tok_stk) - 1;
// 	parse_ast.dir = 1;
// 	parse_ast.paren_lvl = 0;
// 	ast = &g->ast;
// 	ast_recursive(g, (void *)&parse_ast);
// }

void	parsing(t_global *g)
{
	parsing_tokens(g);
	check_syntax(g);
	// parsing_ast(g);
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
