/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 03:45:28 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/31 12:28:02 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_error_fork(t_global *g, pid_t pid, int pipe_fd[2])
{
	if (pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_exit(g, "Fork", -1, 1);
	}
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
		return (exec_cmd(g, ast));
	last_exit = exec_ast(g, ast->left);
	return (check_operator(g, ast, last_exit));
}
