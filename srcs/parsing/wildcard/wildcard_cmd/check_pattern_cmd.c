/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pattern_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:31:09 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/12 21:34:27 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	join_cmd_matchs(t_global *g, t_cmd **new, char *path, char *name)
{
	char	*new_subw;
	t_cmd	*last;

	new_subw = ft_strjoin(path, name);
	if (!new_subw)
	{
		free(path);
		lstfree_cmd(*new);
		exit_free(g, "Malloc", -1, 1);
	}
	lstadd_back_cmd(g, new, NULL);
	last = lstget_last_nd_cmd(*new);
	last->subcmd = lstnew_nd_subcmd(g, ft_strlen(new_subw));
	ft_strcpy(lstget_last_nd_subcmd(last->subcmd)->subword, new_subw);
	free(new_subw);
}
t_cmd	*check_match_wildcards_cmd(t_global *g, char *pattern, char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	t_cmd			*newcmd;

	newcmd = NULL;
	dir = handle_opendir(path);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_pattern(pattern, entry->d_name))
			join_cmd_matchs(g, &newcmd, path, entry->d_name);
		entry = readdir(dir);
	}
	return (newcmd);
}
