/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:56:40 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 00:47:22 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_ambiguous_redir(t_subcmd *top)
{
	while (top && top->next)
	{
		if (top->state == NORMAL && top->next->state == NORMAL)
			return (1);
		top = top->next;
	}
	return (0);
}

int	make_expand_file(t_global *g, t_cmds *cmds, t_file *file, char *name)
{
	if (file && file->redir != HERE_DOC)
	{
		handle_expand_file(g, cmds);
		if (is_ambiguous_redir(file->subcmd))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			free(name);
			return (0);
		}
		handle_wildcard_file(g, cmds);
		if (is_ambiguous_redir(file->subcmd))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			free(name);
			return (0);
		}
	}
	free(name);
	return (1);
}

void	handle_redir_in(t_global *g, t_file *cur, int *last_in)
{
	char *file;
	
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
	char *file;
	
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

void dup_last_file(int last_in, int last_out)
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
