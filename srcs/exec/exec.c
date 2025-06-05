/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 03:45:28 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/05 11:46:25 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

pid_t   handle_error_fork(t_global *g, pid_t pid, int pipe_fd[2])
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
	int	last_exit;

	last_exit = 0;
	if (!ast)
		return (last_exit);
	if (ast->type == PIPE)
		return (exec_pipe(g, ast->left, ast->right));
	if (ast->type == CMD)
		return (exec_cmd(g, ast->cmds));
	last_exit = exec_ast(g, ast->left);
	return (check_operator(g, ast, last_exit));
}
