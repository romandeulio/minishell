/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:27:16 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:36:35 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	join_subcmd_file(t_global *g, t_file *file)
{
	char		*tmp;
	t_subcmd	*cur;
	t_subcmd	*next;

	cur = file->subcmd;
	while (cur)
	{
		next = cur->next;
		if (next && cur->state != next->state)
		{
			tmp = cur->subword;
			cur->subword = ft_strjoin(tmp, next->subword);
			if (!cur->subword)
				exit_free(g, "Malloc", -1, 1);
			cur->next = next->next;
			lstdelete_subcmd(&file->subcmd, next);
			free(tmp);
			continue ;
		}
		cur = cur->next;
	}
}

void	expand_subcmd_file(t_global *g, t_file *cur_file, t_subcmd **subcmd)
{
	t_subcmd	*new;

	if ((*subcmd)->varenv)
	{
		if (!check_dollar_alone(*subcmd))
			new_subw_expand(g, *subcmd);
		(*subcmd)->varenv = 0;
		if (handle_dlt_subcmd(&cur_file->subcmd, subcmd))
			return ;
		new = separate_subcmd(g, *subcmd);
		if (new)
		{
			lstreplace_nd_subcmd(&cur_file->subcmd, *subcmd, new);
			*subcmd = new;
		}
	}
	*subcmd = (*subcmd)->next;
}

int	handle_expand_file(t_global *g, t_cmds *cmds)
{
	t_file		*file;
	t_subcmd	*subcmd;

	file = cmds->file;
	while (file)
	{
		subcmd = file->subcmd;
		while (subcmd)
			expand_subcmd_file(g, file, &subcmd);
		if (handle_dlt_file_nd(&cmds->file, &file))
			continue ;
		file = file->next;
	}
	if (!cmds->file)
		return (0);
	return (1);
}
