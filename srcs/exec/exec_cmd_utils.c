/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:04:31 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/07 21:35:51 by nicolasbrec      ###   ########.fr       */
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

char	*get_cmd_path(t_global *g, t_cmd *top)
{
	int		i;
	char	*path_line;
	char	*slash_cmd;
	char	*real_path;
	char	**all_path;

    if (access(join_subword(g, *(top->subtok)), X_OK) == 0)
        return (join_subword(g, *(top->subtok)));
    path_line = getenv("PATH");
	all_path = ft_split(path_line, ':');
	slash_cmd = ft_strjoin("/", join_subword(g, *(top->subtok)));
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
	return (join_subword(g, *(top->subtok)));
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

	cmd_arg = malloc(sizeof(char *) * (count_arg(top) + 1));
	if (!cmd_arg)
		exit_free(g, "Malloc", -1, 1); // Rajoutez ce qu'il y a a free.
	i = 0;
	while (top)
	{
		cmd_arg[i++] = join_subword(g, *(top->subtok));
		top = top->next;
	}
	cmd_arg[i] = NULL;
	return (cmd_arg);
}

void check_pathname(t_global *g, char *pathname)
{
    if (access(pathname, X_OK) == -1)
    {
        ft_putstr_fd(pathname, 2);
        ft_putendl_fd(": command not found", 2);
        free(pathname);
        exit_free(g, NULL, 2, 127);
    }
}
