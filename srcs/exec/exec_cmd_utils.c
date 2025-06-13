/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:04:31 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:33:28 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_path_line(t_global *g, char *line)
{
	int	i;

	i = 0;
	while (g->env[i])
	{
		if (ft_strncmp(g->env[i], line, ft_strlen(line)) == 0)
			return (g->env[i]);
		i++;
	}
	return (NULL);
}

char	*get_real_path(char **all_path, char *slash_cmd)
{
	int		i;
	char	*real_path;

	i = 0;
	while (all_path[i])
	{
		real_path = ft_strjoin(all_path[i++], slash_cmd);
		if (access(real_path, X_OK) == 0)
		{
			free_tabstr(all_path);
			free(slash_cmd);
			return (real_path);
		}
		free(real_path);
	}
	free_tabstr(all_path);
	free(slash_cmd);
	return (NULL);
}

char	*get_cmd_path(t_global *g, t_cmd *top)
{
	char	*origin_path;
	char	*real_path;
	char	*path_line;
	char	*slash_cmd;
	char	**all_path;

	if (!top)
		return (NULL);
	origin_path = join_subw_subcmd(g, top->subcmd);
	if (access(origin_path, X_OK) == 0)
		return (origin_path);
	path_line = ft_getenv(g->env, "PATH");
	if (!path_line)
		return (origin_path);
	all_path = ft_split(path_line, ':');
	slash_cmd = ft_strjoin("/", origin_path);
	real_path = get_real_path(all_path, slash_cmd);
	if (real_path && path_line)
	{
		free(origin_path);
		return (real_path);
	}
	return (origin_path);
}

int	count_arg(t_cmd *top)
{
	int	count;

	count = 0;
	while (top)
	{
		count++;
		top = top->next;
	}
	return (count);
}

char	**get_cmds_in_tab(t_global *g, t_cmd *top)
{
	int		i;
	char	**cmd_arg;

	if (!top)
		return (NULL);
	cmd_arg = malloc(sizeof(char *) * (count_arg(top) + 1));
	if (!cmd_arg)
		exit_free(g, "Malloc", -1, 1);
	i = 0;
	while (top)
	{
		cmd_arg[i++] = join_subw_subcmd(g, top->subcmd);
		top = top->next;
	}
	cmd_arg[i] = NULL;
	return (cmd_arg);
}
