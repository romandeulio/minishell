/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:56:40 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:46:04 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_redir_in(t_global *g, t_file *cur, int *last_in)
{
	char	*file;

	file = join_subw_subcmd(g, cur->subcmd);
	if (cur->redir == IN_REDIR)
	{
		if (*last_in != -1)
			close(*last_in);
		*last_in = open(file, O_RDONLY);
	}
	else if (cur->redir == HERE_DOC)
	{
		if (*last_in != -1)
			close(*last_in);
		*last_in = cur->heredoc_fd;
	}
	free(file);
}

void	handle_redir_out(t_global *g, t_file *cur, int *last_out)
{
	char	*file;

	file = join_subw_subcmd(g, cur->subcmd);
	if (cur->redir == OUT_REDIR)
	{
		if (*last_out != -1)
			close(*last_out);
		*last_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (cur->redir == APPEND)
	{
		if (*last_out != -1)
			close(*last_out);
		*last_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	free(file);
}

void	dup_last_file(int last_in, int last_out)
{
	if (last_in != -1)
	{
		dup2(last_in, STDIN_FILENO);
		close(last_in);
	}
	if (last_out != -1)
	{
		dup2(last_out, STDOUT_FILENO);
		close(last_out);
	}
}

int	exec_cmdfile(t_global *g, t_cmds *cmds)
{
	t_file	*cur;
	int		last_in;
	int		last_out;
	char	*name_origin;

	last_in = -1;
	last_out = -1;
	cur = cmds->file;
	while (cur)
	{
		name_origin = join_subw_subcmd(g, cur->subcmd);
		if (!make_expand_file(g, cmds, cur, name_origin))
			return (0);
		handle_redir_in(g, cur, &last_in);
		handle_redir_out(g, cur, &last_out);
		if ((cur->redir == IN_REDIR || cur->redir == HERE_DOC) && last_in == -1)
			exit_free(g, "Open", -1, 1);
		if ((cur->redir == OUT_REDIR || cur->redir == APPEND) && last_out == -1)
			exit_free(g, "Open", -1, 1);
		cur = cur->next;
	}
	dup_last_file(last_in, last_out);
	return (1);
}
