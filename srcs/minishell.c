/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:21:59 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/06 17:09:24 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signal = 0;

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

	printf("\033[1;31mVISUALISATION DES TOKENS :\033[0m\n");
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
			printf(" (varenv = %d)", subtok->varenv);
			printf(" (wildcard = %d)", subtok->wildcard);
			subtok = subtok->next;
		}
		printf("\n");
		printf("type = %s\n", type_name[nd->type]);
		nd = nd->next;
		printf("_______________\n");
	}
}

// void	print_ast_pretty(t_ast *ast, const char *prefix, int is_left)
// {
// 	const char *type_name[] = {
// 		"CMD", "PAREN_OPEN", "PAREN_CLOSE",
// 		"IN_REDIR", "OUT_REDIR", "HERE_DOC", "APPEND",
// 		"PIPE", "AND", "OR", "SEMICOLON"
// 	};

// 	if (!ast)
// 		return ;

// 	// ├── ou └── selon la branche
// 	printf("%s%s\033[1;36m[%s]\033[0m (subshell_lvl = %d)\n",
// 		prefix,
// 		is_left ? "├── " : "└── ",
// 		type_name[ast->type],
// 		ast->subshell_lvl);

// 	// affichage des commandes si CMD
// 	if (ast->cmds && ast->type == CMD)
// 	{
// 		t_cmd *cmd = ast->cmds->topcmd;
// 		while (cmd)
// 		{
// 			t_subtok *sub = cmd->subtok;
// 			while (sub)
// 			{
// 				printf("%s│   \033[1;33m→ \"%s\"\033[0m [state: %d, varenv:
//					%d]\n",
// 					prefix, sub->subword, sub->state, sub->varenv);
// 				sub = sub->next;
// 			}
// 			cmd = cmd->next;
// 		}
// 	}

// 	// Préparation du nouveau préfixe
// 	char new_prefix[256];
// 	snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix,
//		is_left ? "│   " : "    ");

// 	// récursivité sur left et right
// 	if (ast->left || ast->right)
// 	{
// 		print_ast_pretty(ast->left, new_prefix, 1);
// 		print_ast_pretty(ast->right, new_prefix, 0);
// 	}
// }

void	print_subtok(t_subtok *subtok)
{
	const char	*state_name[] = {"NORMAL", "SQ", "DQ"};
	int			i;

	i = 1;
	while (subtok)
	{
		if (i > 1)
			printf("    \033[1;34m| \033[0m");
		printf("\033[1;36m%-10s\033[0m = \"%s\"   ", "subword",
			subtok->subword);
		printf("\033[1;33m%-6s\033[0m = %-6s   ", "state",
			state_name[subtok->state]);
		printf("\033[1;33m%-6s\033[0m = %-1d   ", "varenv", subtok->varenv);
		printf("\033[1;35m%-2s\033[0m = %d", "wildcard", subtok->wildcard);
		printf("\n");
		subtok = subtok->next;
		i++;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd)
	{
		printf("  \033[1;4;34m[CMD #%d]\033[0m\n", i++);
		print_subtok(cmd->subtok);
		cmd = cmd->next;
	}
}

void	print_ast(t_ast *ast)
{
	const char	*type_name[] = {"CMD", "PAREN_OPEN", "PAREN_CLOSE", "IN_REDIR",
			"OUT_REDIR", "HERE_DOC", "APPEND", "PIPE", "AND", "OR",
			"SEMICOLON"};

	if (!ast)
		return ;
	printf("\n\033[1;4;44m=== AST NODE ===\033[0m\n");
	printf("\033[1;32m%-16s\033[0m : %s\n", "type", type_name[ast->type]);
	printf("\033[1;32m%-16s\033[0m : %d\n", "subshell_lvl", ast->subshell_lvl);
	if (ast->cmds)
	{
		printf("\033[1;4;34m[COMMANDS]\033[0m\n");
		print_cmd(ast->cmds->topcmd);
		printf("\033[1;34m%-16s\033[0m : %s\n", "file", ast->cmds->file);
		printf("\033[1;34m%-16s\033[0m : %d\n", "heredoc_fd",
			ast->cmds->heredoc_fd);
		printf("\033[1;34m%-16s\033[0m : %s\n", "file redir",
			type_name[ast->cmds->redir]);
	}
	print_ast(ast->left);
	print_ast(ast->right);
}

void	parsing(t_global *g)
{
	t_tok_nd	*start;
	t_tok_nd	*end;

	//printf("\033[1;32mNOUVELLE COMMANDE :\033[0m\n");
	parsing_tokens(g);
	handle_expand(g);
	//print_token(g); // temporaire
	if (g->error_line || check_syntax(g, 1))
		return ;
	lstinit_prev_node_tok(g->tok_stk.top);
	start = g->tok_stk.top;
	end = lstget_last_nd_tok(g->tok_stk.top);
	g->ast = parsing_ast(g, start, end);
	// printf("\033[1;4;45m🌳 AST VISUALISÉ :\033[0m\n");
	// print_ast(g->ast);
}

void	minishell(t_global *g)
{
	while (1)
	{
		g->rd.line = readline(get_cur_dir(g));
		if (!g->rd.line)
		{
			free_and_reset_readline(g);
			rl_clear_history();
			ft_putendl_fd("Exit", 1);
			exit(0);
		}
		else
		{
			g->rd.full_line = ft_strdup(g->rd.line);
			parsing(g);
			check_and_add_history(g->rd.full_line);
			if (!g->error_line)
				exec_ast(g, g->ast);
		}
		reinit_new_line(g);
	}
}

int	main(int ac, char **av, char **env)
{
	t_global	g;

	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("Usage: ./Minishell", 2);
		return (1);
	}
	ft_bzero(&g, sizeof(t_global));
	env_cpy(&g, env, tab_size(env));
	g.env = env_cpy(&g, env, tab_size(env));
	g.is_interactive = isatty(0);
	if (!g.is_interactive)
		sleep(3);
	// save_termios_state(&g);
	handle_signal(&g);
	minishell(&g);
	return (0);
}
