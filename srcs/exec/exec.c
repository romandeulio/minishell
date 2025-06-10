/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 03:45:28 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/10 17:38:20 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

pid_t	handle_error_fork(t_global *g, pid_t pid, int pipe_fd[2])
{
	if (pid < 0)
	{
		if (pipe_fd)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		exit_free(g, "Fork", -1, 1);
	}
	return (pid);
}

int	exec_ast(t_global *g, t_ast *ast)
{
	if (!ast)
		return (g_exit_code);
	if (ast->type == PIPE)
		return (exec_pipe(g, ast->left, ast->right));
	if (ast->type == PAREN_OPEN)
		return (exec_subshell(g, ast->right));
	if (ast->type == CMD)
		return (exec_cmd(g, ast->cmds));
	g_exit_code = exec_ast(g, ast->left);
	return (check_operator(g, ast, g_exit_code));
}
