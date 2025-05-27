/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:21:59 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/27 17:27:30 by nicolasbrec      ###   ########.fr       */
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
	const char	*state_name[] = {"NORMAL", "SQ", "DQ"};

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
			if (j > 1)
				printf(" | ");
			printf("subword %d = {%s}", j++, subtok->subword);
			printf(" (state = %s)", state_name[subtok->state]);
			subtok = subtok->next;
		}
		printf("\n");
		printf("type = %s\n", type_name[nd->type]);
		nd = nd->next;
		printf("_______________\n");
	}
}

int	get_priority(t_tok_nd *nd)
{
	int	value;

	value = 0;
	if (nd->type == PIPE)
		value = -4;
	else if (nd->type == AND)
		value = -3;
	else if (nd->type == OR)
		value = -2;
	else if (nd->type == SEMICOLON)
		value = -1;
	if (value < 0)
		value = value - (4 * nd->paren_lvl);
	return (value);
}

int	count_join_subword(t_subtok *subtok)
{
	int	count;

	count = 0;
	while (subtok)
	{
		count += ft_strlen(subtok->subword);
		subtok = subtok->next;
	}
	return (count);
}

char	*join_subword(t_global *g, t_subtok *subtok)
{
	char	*allword;
	char	*tmp;

	allword = malloc(sizeof(char) * (count_join_subword(subtok) + 1));
	if (!allword)
		ft_exit("Malloc", g);
	allword = NULL;
	tmp = ft_strdup("");
	while (subtok)
	{
		allword = ft_strjoin(tmp, subtok->subword);
		free(tmp);
		tmp = allword;
		subtok = subtok->next;
	}
	return (allword);
}

void	init_cmdfile(t_global *g, t_cmds *cmds, t_tok_nd *nd)
{
	cmds->infile.file = join_subword(g, nd->next->top);
	cmds->infile.redir = nd->type;
}

t_cmd *lstnew_nd_cmd(t_global *g, t_subtok *nd)
{
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		ft_exit("Malloc", g);
	new->subtok = nd;
	new->next = NULL;
	return (new);
}

void	add_back_cmd(t_global *g, t_cmd **top, t_subtok *nd)
{
	t_cmd	*tmp;

	if (!*top)
	{
		*top = lstnew_nd_cmd(g, nd);
		return ;
	}
	tmp = *top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = lstnew_nd_cmd(g, nd);
}

t_cmds	*new_cmds(t_global *g, t_tok_nd *start, t_tok_nd *end)
{
	t_cmds		*cmds;
	t_tok_nd	*cur;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		ft_exit("Malloc", g); // verif si il faut liberer des trucs en
	cur = start;
	ft_bzero(cmds, sizeof(t_cmds));
	while (1)
	{
		if (is_redir(cur->type))
		{
			init_cmdfile(g, cmds, cur);
			cur = cur->next;
		}
		else if (!is_parenthesis(cur->type))
			add_back_cmd(g, &cmds->topcmd, cur->top);
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (cmds);
}

t_tok_nd	*find_lowest_prio_op(t_tok_nd *start, t_tok_nd *end)
{
	t_tok_nd	*cur;
	t_tok_nd	*lowest_nd;

	cur = start;
	lowest_nd = start;
	while (1)
	{
		if (get_priority(cur) <= get_priority(lowest_nd))
			lowest_nd = cur;
		if (cur == end)
			break ;
		cur = cur->next;
	}
	if (get_priority(lowest_nd) == 0)
		return (NULL);
	return (lowest_nd);
}

int	count_parenlvl_cmd(t_tok_nd *start, t_tok_nd *end)
{
	int			count;
	t_tok_nd	*cur;

	count = 0;
	cur = start;
	while (1)
	{
		if (cur->type == PAREN_OPEN)
			count++;
		if (cur == end)
			break ;
	}
	return (count);
}

t_ast	*create_ast_cmd(t_global *g, t_tok_nd *start, t_tok_nd *end)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		ft_exit("Malloc", g);
	new->type = CMD;
	new->subshell_lvl = start->paren_lvl;
	new->cmds = new_cmds(g, start, end);
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast	*create_ast_op(t_global *g, t_tok_nd *pivot)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		ft_exit("Malloc", g);
	new->type = pivot->type;
	new->subshell_lvl = pivot->paren_lvl;
	new->cmds = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast	*parsing_ast(t_global *g, t_tok_nd *start, t_tok_nd *end)
{
	t_ast		*nd_ast;
	t_tok_nd	*pivot;

	pivot = find_lowest_prio_op(start, end);
	if (!pivot)
		return (create_ast_cmd(g, start, end));
	nd_ast = create_ast_op(g, pivot);
	nd_ast->left = parsing_ast(g, start, pivot->prev);
	nd_ast->right = parsing_ast(g, pivot->next, end);
	return (nd_ast);
}

void	parsing(t_global *g)
{
	t_tok_nd	*start;
	t_tok_nd	*end;

	parsing_tokens(g);
	print_token(g);
	check_syntax(g);
	lstconnect_prev_node_tok(g->tok_stk.top);
	start = g->tok_stk.top;
	end = lstget_last_nd_tok(g->tok_stk.top);
	g->ast = parsing_ast(g, start, end);
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
			g->rd.full_line = g->rd.line;
			parsing(g);
			check_and_add_history(g->rd.full_line);
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
