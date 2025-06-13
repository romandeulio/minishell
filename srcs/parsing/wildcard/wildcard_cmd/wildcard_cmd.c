/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:29:34 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 14:16:02 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	join_subcmd_in_allcmd(t_global *g, t_cmd *cmd, t_subcmd *rest, int i)
{
	t_subcmd	*subcmd;

	while (cmd)
	{
		subcmd = cmd->subcmd;
		while (subcmd && subcmd->next)
			subcmd = subcmd->next;
		subcmd->next = get_rest_in_subcmd(g, rest, i);
		cmd = cmd->next;
	}
}

void	lstswap_cmd(t_cmd **top, t_cmd *n1, t_cmd *n2)
{
	t_cmd	*cur;
	t_cmd	*prev;

	if (!top || !*top || !n1 || !n2 || n1->next != n2)
		return ;
	cur = *top;
	prev = NULL;
	while (cur)
	{
		if (cur == n1)
		{
			if (!prev)
				*top = n2;
			else
				prev->next = n2;
			n1->next = n2->next;
			n2->next = n1;
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	lstsort_cmd(t_cmd **top)
{
	int		swapped;
	t_cmd	*cur;
	char	*a;
	char	*b;

	if (!top || !*top)
		return ;
	swapped = 1;
	while (swapped)
	{
		cur = *top;
		swapped = 0;
		while (cur && cur->next)
		{
			a = cur->subcmd->subword;
			b = cur->next->subcmd->subword;
			if (a && b && ft_strcmp(a, b) > 0)
			{
				lstswap_cmd(top, cur, cur->next);
				swapped = 1;
				break ;
			}
			cur = cur->next;
		}
	}
}

t_cmd	*browse_paths_wildcard_cmd(t_global *g, t_subcmd *subcmd)
{
	t_cmd	*new;
	char	*wildcard_word;
	char	*full_path;
	int		path_len;
	int		i;

	new = lstnew_nd_cmd(g, NULL);
	i = 0;
	path_len = lenpath_wildcard(subcmd);
	full_path = NULL;
	if (path_len > 0)
		full_path = file_full_path(g, &subcmd, &i, path_len);
	wildcard_word = get_wildcard_word(g, subcmd, i, full_path);
	new = check_match_wildcards_cmd(g, wildcard_word, full_path);
	lstsort_cmd(&new);
	if (new)
		join_subcmd_in_allcmd(g, new, subcmd, i);
	free(full_path);
	return (new);
}

void	handle_wildcard_cmd(t_global *g, t_cmds *cmds)
{
	t_cmd		*cmd;
	t_cmd		*new;
	t_subcmd	*subcmd;

	cmd = cmds->topcmd;
	while (cmd)
	{
		subcmd = cmd->subcmd;
		while (subcmd)
		{
			if (subcmd->wildcard)
			{
				new = browse_paths_wildcard_cmd(g, cmd->subcmd);
				lstreplace_nd_cmd(&cmds->topcmd, cmd, new);
				if (new)
				{
					cmd = new;
					subcmd = cmd->subcmd;
					continue ;
				}
			}
			subcmd = subcmd->next;
		}
		cmd = cmd->next;
	}
}
