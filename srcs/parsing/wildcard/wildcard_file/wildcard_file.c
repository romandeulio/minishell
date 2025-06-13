/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:30:19 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 17:48:35 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	join_rest_all_subcmd(t_global *g, t_subcmd *subcmd, t_subcmd *rest, int i)
{
	while (subcmd && subcmd->next)
		subcmd = subcmd->next;
	subcmd->next = get_rest_in_subcmd(g, rest, i);
}

void	lstswap_subcmd(t_subcmd **top, t_subcmd *n1, t_subcmd *n2)
{
	t_subcmd	*cur;
	t_subcmd	*prev;

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

void	lstsort_subcmd(t_subcmd **top)
{
	int			swapped;
	t_subcmd	*cur;
	char		*a;
	char		*b;

	if (!top || !*top)
		return ;
	swapped = 1;
	while (swapped)
	{
		cur = *top;
		swapped = 0;
		while (cur && cur->next)
		{
			a = cur->subword;
			b = cur->next->subword;
			if (a && b && ft_strcmp(a, b) > 0)
			{
				lstswap_subcmd(top, cur, cur->next);
				swapped = 1;
				break ;
			}
			cur = cur->next;
		}
	}
}

t_subcmd	*browse_paths_wildcard_file(t_global *g, t_subcmd *subcmd)
{
	t_subcmd	*new;
	char		*wildcard_word;
	char		*full_path;
	int			path_len;
	int			i;

	i = 0;
	path_len = lenpath_wildcard(subcmd);
	full_path = NULL;
	if (path_len > 0)
		full_path = file_full_path(g, &subcmd, &i, path_len);
	wildcard_word = get_wildcard_word(g, subcmd, i, full_path);
	new = check_match_wildcards_file(g, wildcard_word, full_path);
	free(wildcard_word);
	lstsort_subcmd(&new);
	if (new)
		join_rest_all_subcmd(g, new, subcmd, i);
	return (new);
}

void	handle_wildcard_file(t_global *g, t_cmds *cmds)
{
	t_file		*file;
	t_subcmd	*new;
	t_subcmd	*subcmd;

	file = cmds->file;
	while (file)
	{
		subcmd = file->subcmd;
		while (subcmd)
		{
			if (subcmd->wildcard)
			{
				new = browse_paths_wildcard_file(g, file->subcmd);
				if (new)
				{
					lstreplace_nd_subcmd(&file->subcmd, subcmd, new);
					subcmd = new;
					continue ;
				}
			}
			subcmd = subcmd->next;
		}
		file = file->next;
	}
}
