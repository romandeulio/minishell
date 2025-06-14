/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:21:59 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/13 18:34:45 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_exit_code = 0;

// void	print_token(t_global *g)
// {
// 	int			i;
// 	int			j;
// 	int			size;
// 	t_tok_stk	*stk;
// 	t_tok_nd	*nd;
// 	t_subtok	*subtok;
// 	const char	*type_name[] = {"CMD", "PAREN_OPEN", "PAREN_CLOSE", "IN_REDIR",
// 			"OUT_REDIR", "HERE_DOC", "APPEND", "PIPE", "AND", "OR",
// 			"SEMICOLON"};
// 	const char	*state_name[] = {"NORMAL", "SQ", "DQ"};

// 	printf("\033[1;31mVISUALISATION DES TOKENS :\033[0m\n");
// 	size = lstcount_nd_tok(&g->tok_stk);
// 	i = 1;
// 	stk = &g->tok_stk;
// 	nd = stk->top;
// 	printf("_______________\n");
// 	while (nd)
// 	{
// 		j = 1;
// 		subtok = nd->top;
// 		printf("Word %d/%d :\n", i++, size);
// 		printf("nd->paren_lvl = %d\n", nd->paren_lvl);
// 		while (subtok)
// 		{
// 			if (j > 1)
// 				printf(" | ");
// 			printf("subword %d = {%s}", j++, subtok->subword);
// 			printf(" (state = %s)", state_name[subtok->state]);
// 			printf(" (varenv = %d)", subtok->varenv);
// 			printf(" (wildcard = %d)", subtok->wildcard);
// 			subtok = subtok->next;
// 		}
// 		printf("\n");
// 		printf("type = %s\n", type_name[nd->type]);
// 		nd = nd->next;
// 		printf("_______________\n");
// 	}
// }

// void	print_subcmd(t_subcmd *subcmd)
// {
// 	const char	*state_name[] = {"NORMAL", "SQ", "DQ"};
// 	int			i;

// 	i = 1;
// 	while (subcmd)
// 	{
// 		if (i > 1)
// 			printf("    \033[1;34m| \033[0m");
// 		printf("\033[1;36m%-10s\033[0m = \"%s\"   ", "subword",
// 			subcmd->subword ? subcmd->subword : "(null)");
// 		printf("\033[1;33m%-6s\033[0m = %-6s   ", "state", (subcmd->state >= 0
// 				&& subcmd->state <= 2) ? state_name[subcmd->state] : "???");
// 		printf("\033[1;33m%-6s\033[0m = %-1d   ", "varenv", subcmd->varenv);
// 		printf("\033[1;35m%-9s\033[0m = %d", "wildcard", subcmd->wildcard);
// 		printf("\n");
// 		subcmd = subcmd->next;
// 		i++;
// 	}
// }

// void	print_file(t_file *file)
// {
// 	const char	*type_name[] = {"CMD", "PAREN_OPEN", "PAREN_CLOSE", "IN_REDIR",
// 			"OUT_REDIR", "HERE_DOC", "APPEND", "PIPE", "AND", "OR",
// 			"SEMICOLON"};
// 	int			i;

// 	i = 1;
// 	while (file)
// 	{
// 		printf("  \033[1;4;35m[FILE REDIR #%d]\033[0m\n", i++);
// 		if (file->subcmd)
// 		{
// 			printf("  \033[1;36m%-16s\033[0m :\n", "subcmds");
// 			print_subcmd(file->subcmd);
// 		}
// 		else
// 		{
// 			printf("  \033[1;36m%-16s\033[0m : (null)\n", "subcmds");
// 		}
// 		printf("\033[1;34m%-16s\033[0m : %d\n", "heredoc_fd", file->heredoc_fd);
// 		printf("\033[1;34m%-16s\033[0m : %s\n", "file redir", (file->redir >= 0
// 				&& file->redir <= 10) ? type_name[file->redir] : "???");
// 		file = file->next;
// 	}
// }

// void	print_cmd(t_cmd *cmd)
// {
// 	int	i;

// 	i = 1;
// 	while (cmd)
// 	{
// 		printf("  \033[1;4;34m[CMD #%d]\033[0m\n", i++);
// 		print_subcmd(cmd->subcmd);
// 		cmd = cmd->next;
// 	}
// }

// void	print_ast(t_ast *ast, const char *branch_label)
// {
// 	const char	*type_name[] = {"CMD", "PAREN_OPEN", "PAREN_CLOSE", "IN_REDIR",
// 			"OUT_REDIR", "HERE_DOC", "APPEND", "PIPE", "AND", "OR",
// 			"SEMICOLON"};

// 	if (!ast)
// 		return ;
// 	printf("\n\033[1;4;44m=== AST NODE (%s) ===\033[0m\n", branch_label);
// 	printf("\033[1;32m%-16s\033[0m : %s\n", "type", (ast->type >= 0
// 			&& ast->type <= 10) ? type_name[ast->type] : "???");
// 	if (ast->cmds)
// 	{
// 		if (ast->cmds->topcmd)
// 		{
// 			printf("\033[1;4;34m[COMMANDS]\033[0m\n");
// 			print_cmd(ast->cmds->topcmd);
// 		}
// 		if (ast->cmds->file)
// 			print_file(ast->cmds->file);
// 	}
// 	print_ast(ast->left, "left");
// 	print_ast(ast->right, "right");
// }

void	parsing(t_global *g)
{
	t_tok_nd	*start;
	t_tok_nd	*end;

	parsing_tokens(g);
	if (g->error_line || check_syntax(g, 1))
		return ;
	lstinit_prev_node_tok(g->tok_stk.top);
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
		{
			free_and_reset_readline(g);
			rl_clear_history();
			ft_putendl_fd("Exit", 1);
			free_tabstr(g->env);
			exit(g_exit_code);
		}
		else
		{
			g->rd.full_line = ft_strdup(g->rd.line);
			parsing(g);
			check_and_add_history(g->rd.full_line);
			if (!g->error_line)
				g_exit_code = exec_ast(g, g->ast);
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
	check_env(&g, env);
	g.is_interactive = isatty(0);
	handle_signal(&g);
	minishell(&g);
	return (0);
}
