/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:12:03 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/07 13:08:43 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void print_cmd_arg(char **cmd_arg)
// {
//     int i;

//     i = 0;
//     while (cmd_arg[i])
//     {
//         printf("cmd_arg[%d] = %s\n", i, cmd_arg[i]);
//         i++;
//     }
// }

void	exec_cmd_fork(t_global *g, t_cmds *cmds, char *path, char **args)
{
    exec_cmdfile(g, cmds);
    check_pathname(g, path);
    free_before_execve(g);
	if (execve(path, args, g->env) == -1)
	{
		free(path);
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

    if (!handle_expand(g, cmds))
        return (0);
	pathname = get_cmd_path(g, cmds->topcmd);
	g->tmp.cmd_arg = get_cmds_in_tab(g, cmds->topcmd);
	if (check_builtin(g, g->tmp.cmd_arg))
		return (0);
	pid = handle_error_fork(g, fork(), NULL);
	if (pid == 0)
		exec_cmd_fork(g, cmds, pathname, g->tmp.cmd_arg);
	free(pathname);
	free_tabstr(g->tmp.cmd_arg);
	waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}
