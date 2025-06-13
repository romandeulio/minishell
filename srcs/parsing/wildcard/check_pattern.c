/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:35:21 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:39:55 by nbrecque         ###   ########.fr       */
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
