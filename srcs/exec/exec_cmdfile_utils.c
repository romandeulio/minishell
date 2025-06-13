/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdfile_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:43:49 by nbrecque          #+#    #+#             */
/*   Updated: 2025/06/13 18:46:02 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_ambiguous_redir(t_subcmd *top)
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
