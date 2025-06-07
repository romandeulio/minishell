/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:56:40 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/07 14:50:37 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_in_redir(t_global *g, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_free(g, "Open", -1, 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_out_redir(t_global *g, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_free(g, "Open", -1, 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_heredoc_redir(t_cmds *cmds)
{
	dup2(cmds->heredoc_fd, STDIN_FILENO);
	close(cmds->heredoc_fd);
}

void	handle_append_redir(t_global *g, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit_free(g, "Open", -1, 1); // voir les autres variable a free
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	exec_cmdfile(t_global *g, t_cmds *cmds)
{
	if (cmds->file)
	{
		if (cmds->redir == IN_REDIR)
			handle_in_redir(g, cmds->file);
		else if (cmds->redir == OUT_REDIR)
			handle_out_redir(g, cmds->file);
		else if (cmds->redir == HERE_DOC)
			handle_heredoc_redir(cmds);
		else if (cmds->redir == APPEND)
			handle_append_redir(g, cmds->file);
	}
}
