/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:35:21 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/11 15:34:04 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
	{
		perror("Stat");
		return (0);
	}
	return (S_ISDIR(sb.st_mode));
}

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
	lstget_last_nd_subcmd(last->subcmd)->subword = new_subw;
}

DIR	*handle_opendir(char *path)
{
	DIR	*dir;

	if (path)
	{
		if (!is_directory(path))
			return (NULL);
		dir = opendir(path);
		if (!dir)
			return (NULL);
	}
	else
	{
		dir = opendir(".");
		if (!dir)
			return (NULL);
	}
	return (dir);
}

t_cmd	*check_match_wildcards(t_global *g, char *pattern, char *path)
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

int	match_pattern(char *pattern, char *filename)
{
	if (pattern[0] == '\0' && filename[0] == '\0')
		return (1);
	if (pattern[0] == '\0')
		return (0);
	if (pattern[0] == '*')
	{
		pattern++;
		if (pattern[0] == '\0')
			return (1);
		while (filename[0] != '\0')
		{
			if (match_pattern(pattern, filename))
				return (1);
			filename++;
		}
		return (match_pattern(pattern, filename));
	}
	if (filename[0] == '\0')
		return (0);
	if (pattern[0] == filename[0])
		return (match_pattern(pattern + 1, filename + 1));
	return (0);
}
