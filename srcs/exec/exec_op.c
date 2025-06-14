/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:12:01 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/11 16:23:34 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_subshell(t_global *g, t_ast *ast_right)
{
	pid_t	pid;
	int		status;
	int		code;

	pid = handle_error_fork(g, fork(), NULL);
	if (pid == 0)
	{
		code = exec_ast(g, ast_right);
		free_in_fork(g);
		exit(code);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

void	exec_pipe_fork(t_global *g, t_ast *ast, int p_fd[2], int n_cmd)
{
	int	code;

	if (n_cmd == 1)
	{
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
		close(p_fd[0]);
		code = exec_ast(g, ast);
		free_in_fork(g);
		exit(code);
	}
	else if (n_cmd == 2)
	{
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
		close(p_fd[1]);
		code = exec_ast(g, ast);
		free_in_fork(g);
		exit(code);
	}
}

int	exec_pipe(t_global *g, t_ast *ast_left, t_ast *ast_right)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (pipe(pipe_fd) == -1)
		exit_free(g, "Pipe", -1, 1);
	pid1 = handle_error_fork(g, fork(), pipe_fd);
	if (pid1 == 0)
		exec_pipe_fork(g, ast_left, pipe_fd, 1);
	pid2 = handle_error_fork(g, fork(), pipe_fd);
	if (pid2 == 0)
		exec_pipe_fork(g, ast_right, pipe_fd, 2);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return (WEXITSTATUS(status2));
}

int	check_operator(t_global *g, t_ast *ast, int last_exit)
{
	if (ast->type == AND)
	{
		if (last_exit == 0)
			last_exit = exec_ast(g, ast->right);
		return (last_exit);
	}
	else if (ast->type == OR)
	{
		if (last_exit != 0)
			last_exit = exec_ast(g, ast->right);
		return (last_exit);
	}
	else if (ast->type == SEMICOLON)
		return (exec_ast(g, ast->right));
	return (0);
}
