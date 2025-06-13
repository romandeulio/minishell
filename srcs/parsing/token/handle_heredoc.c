/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:53:47 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:39:08 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	read_heredoc_redir(int fd[2], char *stop)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, stop))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	close(fd[0]);
}

int	exec_heredoc(t_global *g, char *stop)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		exit_free(g, "Pipe", -1, 1);
	pid = handle_error_fork(g, fork(), fd);
	if (pid == 0)
	{
		reinit_sig_heredoc();
		disable_echoctl();
		read_heredoc_redir(fd, stop);
		enable_echoctl();
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		g_exit_code = SIGINT;
		return (-1);
	}
	return (fd[0]);
}

void	check_heredoc(t_global *g, t_tok_nd *first)
{
	t_tok_nd	*cur;
	t_tok_nd	*next;

	if (first)
		cur = first;
	else
		cur = g->tok_stk.top;
	while (cur)
	{
		next = cur->next;
		if (cur->type == HERE_DOC && next && next->type == CMD)
			next->heredoc_fd = exec_heredoc(g, join_subw_subtok(g, next->top));
        cur = next;
	}
}
