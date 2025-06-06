/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:12:03 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/06 17:09:35 by nicolasbrec      ###   ########.fr       */
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

    if (access(join_subword(g, top->subtok), X_OK) == 0)
        return (join_subword(g, top->subtok));
    path_line = getenv("PATH");
	all_path = ft_split(path_line, ':');
	slash_cmd = ft_strjoin("/", join_subword(g, top->subtok));
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
	return (join_subword(g, top->subtok));
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
		cmd_arg[i++] = join_subword(g, top->subtok);
		top = top->next;
	}
	cmd_arg[i] = NULL;
	return (cmd_arg);
}

void print_cmd_arg(char **cmd_arg)
{
    int i;

    i = 0;
    while (cmd_arg[i])
    {
        printf("cmd_arg[%d] = %s\n", i, cmd_arg[i]);
        i++;
    }
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

void	exec_cmd_fork(t_global *g, char *pathname, char **cmd_arg)
{
    check_pathname(g, pathname);
	if (execve(pathname, cmd_arg, g->env) == -1)
	{
		free(pathname);
		exit_free(g, "Execve", -1, 1);
	}
}

int	check_builtin(t_global *g, char **cmd_arg)
{
	if (!ft_strcmp("cd", cmd_arg[0]))
		ft_cd(g, cmd_arg);
	if (!ft_strcmp("echo", cmd_arg[0]))
		ft_echo(cmd_arg);
	else if (!ft_strcmp("env", cmd_arg[0]))
		ft_env(g);
	else if (!ft_strcmp("exit", cmd_arg[0]))
		ft_exit(g, cmd_arg);
	else if (!ft_strcmp("export", cmd_arg[0]))
		ft_export(g, cmd_arg);
	else if (!ft_strcmp("pwd", cmd_arg[0]))
		ft_pwd();
    else if (!ft_strcmp("unset", cmd_arg[0]))
        ft_unset(g, cmd_arg);
    else
        return (0);
	return (1);
}

int exec_cmd(t_global *g, t_cmds *cmds)
{
	pid_t	pid;
	int		status;
	char	*pathname;

	exec_cmdfile(g, cmds);
	pathname = get_cmd_path(g, cmds->topcmd);
	g->tmp.cmd_arg = get_cmds_in_tab(g, cmds->topcmd);
	if (check_builtin(g, g->tmp.cmd_arg))
		return (0);
	pid = handle_error_fork(g, fork(), NULL);
	if (pid == 0)
		exec_cmd_fork(g, pathname, g->tmp.cmd_arg);
	free(pathname);
	free_tabstr(g->tmp.cmd_arg);
	waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}
