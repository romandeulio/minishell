/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:53:47 by nicolasbrec       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/07 02:07:07 by nicolasbrec      ###   ########.fr       */
=======
/*   Updated: 2025/06/06 17:22:08 by nicolasbrec      ###   ########.fr       */
>>>>>>> d31cb04 (corr heredoc)
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// char	*readline_heredoc(t_global *g)
// {
// 	int		rd_bytes;
// 	char	buf[2];
// 	char	*line;
// 	char	*tmp;

// 	buf[1] = '\0';
// 	line = NULL;
// 	while (ft_strncmp(buf, "\n", 1))
// 	{
// 		rd_bytes = read(0, buf, 1);
// 		if (rd_bytes == 0)
// 			return (NULL);
// 		if (rd_bytes == -1)
// 		{
// 			free(line);
// 			ft_exit(g, "Read", -1, 1);
// 		}
// 		tmp = line;
// 		line = ft_strjoin(tmp, buf);
// 		free(tmp);
// 		if (!line)
// 			ft_exit(g, "Malloc", -1, 1);
// 	}
// 	return (line);
// }

// void	handle_heredoc_redir(t_global *g, char *stop)
// {
// 	char	*line;
// 	int		fd[2];
// 	int		line_len;
// 	int		stp_len;

// 	if (pipe(fd) == -1)
// 		ft_exit(g, "Pipe", -1, 1); // voir les autres variable a free
// 	write(1, "> ", 2);
// 	stp_len = ft_strlen(stop);
// 	while (1)
// 	{
// 		line = readline_heredoc(g);
// 		line_len = ft_strlen(line) - 1;
// 		if (!line || (!ft_strncmp(line, stop, stp_len) && line_len == stp_len))
// 			break ;
// 		write(1, "> ", 2);
// 		write(fd[1], line, ft_strlen(line));
// 		free(line);
// 	}
// 	free(line);
// 	close(fd[1]);
// }

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
    write(fd[1], "\n", 1);
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
		exit_free(g, "Pipe", -1, 1); // voir les autres variable a free
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
		g_signal = SIGINT;
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
			next->heredoc_fd = exec_heredoc(g, join_subword(g, next->top));
        cur = next;
	}
}
