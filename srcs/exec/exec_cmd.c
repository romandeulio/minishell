/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:12:03 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/01 16:02:24 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_path_line(t_global *g, char *line)
{
	int		i;
	char	*path_line;

	i = 0;
	while (g->env[i])
	{
		if (ft_strncmp(g->env[i], line, ft_strlen(line)) == 0)
			return (g->env[i]);
		i++;
	}
	return (NULL);
}

int	get_cmd_path(t_global *g, t_cmd *top)
{
	int		i;
	char	*path_line;
	char	*slash_cmd;
	char	*real_path;
	char	**all_path;

	path_line = get_path_line(g, "PATH=");
	all_path = ft_split(path_line, ':');      // verif l'echec NULL
	slash_cmd = ft_strjoin("/", top->subtok); // verif l'echec NULL
	i = 0;
	while (all_path[i])
	{
		real_path = ft_strjoin(all_path[i++], slash_cmd); // verif l'echec NULL
		if (access(real_path, X_OK))
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
	t_cmd	*cur;

	cmd_arg = malloc(sizeof(char *) * (count_arg(top) + 1));
	if (!cmd_arg)
		ft_exit(g, "Malloc", -1, 1); // Rajoutez ce qu'il y a a free.
    i = 0;
	while (cur)
	{
		cmd_arg[i++] = join_subword(g, cur);
        cur = cur->next;
	}
    cmd_arg[i] = NULL;
	return (cmd_arg);
}

int exec_cmd_fork()
{
    
}

int exec_cmdfile(t_global *g, t_cmds *cmds)
{
    
}

int	exec_cmd(t_global *g, t_cmds *cmds)
{
	char	*pathname;
	char	**cmd_arg;

	pathname = get_cmd_path(g, cmds->topcmd);
	cmd_arg = get_cmds_in_tab(g, cmds->topcmd);

    if (execve(pathname, cmd_arg, g->env) == -1)
    {
        free(pathname);
        free_tabstr(cmd_arg);
        ft_exit(g, "Execve", -1 , 1); // Rajoutez ce qu'il y a à free.
    }
}
