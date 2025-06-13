/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pattern_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:31:44 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:39:44 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	join_subcmd_matchs(t_global *g, t_subcmd **new, char *path, char *name)
{
	char		*new_subw;
	t_subcmd	*last;

	new_subw = ft_strjoin(path, name);
	if (!new_subw)
	{
		free(path);
		lstfree_subcmd(new);
		exit_free(g, "Malloc", -1, 1);
	}
	lstadd_back_subcmd(new, lstnew_nd_subcmd(g, ft_strlen(new_subw)));
	last = lstget_last_nd_subcmd(*new);
	ft_strcpy(lstget_last_nd_subcmd(last)->subword, new_subw);
	free(new_subw);
}

t_subcmd	*check_match_wildcards_file(t_global *g, char *pattern, char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	t_subcmd		*newcmd;

	newcmd = NULL;
	dir = handle_opendir(path);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_pattern(pattern, entry->d_name))
			join_subcmd_matchs(g, &newcmd, path, entry->d_name);
		entry = readdir(dir);
	}
	free(dir);
	return (newcmd);
}
