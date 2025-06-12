/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:56:40 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/12 01:30:42 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_in_redir(t_global *g, char *file)
{
	int	fd;

	// verif si le wildcard a donner plus de 1 fichier
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

void	handle_heredoc_redir(t_file *limiter)
{
	dup2(limiter->heredoc_fd, STDIN_FILENO);
	close(limiter->heredoc_fd);
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

// int check_all_file()
// {
	
// }

void	exec_cmdfile(t_global *g, t_cmds *cmds)
{
	t_file *last;

	last = lstget_last_nd_file(cmds->file);
	if (last && last->redir != HERE_DOC)
	{
		// handle_expand et handle_wildcard
		handle_expand_file(g, cmds);
		handle_wildcard(g, cmds);;
	}
	if (last)
	{
		if (last->redir == IN_REDIR)
			handle_in_redir(g, join_subw_subcmd(g, last->subcmd));
		else if (last->redir == OUT_REDIR)
			handle_out_redir(g, join_subw_subcmd(g, last->subcmd));
		else if (last->redir == HERE_DOC)
			handle_heredoc_redir(last);
		else if (last->redir == APPEND)
			handle_append_redir(g, join_subw_subcmd(g, last->subcmd));
	}
}
