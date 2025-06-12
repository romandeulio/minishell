/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:27:51 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 00:48:05 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void join_subcmd_cmd(t_global *g, t_cmd *cmd)
{
    char *tmp;
    t_subcmd *cur;
    t_subcmd *next;

    cur = cmd->subcmd;
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
            lstdelete_subcmd(&cmd->subcmd, next);
            free(tmp);
            continue;
        }
        cur = cur->next;
    }
}

void	expand_subcmd_cmd(t_global *g, t_cmd *cur_cmd, t_subcmd **subcmd)
{
	t_subcmd	*new;

	if ((*subcmd)->varenv)
	{
		if (!check_dollar_alone(*subcmd))
			new_subw_expand(g, *subcmd);
		(*subcmd)->varenv = 0;
		if (handle_dlt_subcmd(&cur_cmd->subcmd, subcmd))
			return ;
		new = separate_subcmd(g, *subcmd);
		if (new)
		{
			lstreplace_nd_subcmd(&cur_cmd->subcmd, *subcmd, new);
			*subcmd = new;
		}
	}
	*subcmd = (*subcmd)->next;
}

int	handle_expand_cmd(t_global *g, t_cmds *cmds)
{
	t_cmd		*cmd;
	t_subcmd	*subcmd;

	cmd = cmds->topcmd;
	while (cmd)
	{
		subcmd = cmd->subcmd;
		while (subcmd)
			expand_subcmd_cmd(g, cmd, &subcmd);
		if (handle_dlt_cmd_nd(&cmds->topcmd, &cmd))
			continue ;
		cmd = cmd->next;
	}
	if (!cmds->topcmd)
		return (0);
	return (1);
}
