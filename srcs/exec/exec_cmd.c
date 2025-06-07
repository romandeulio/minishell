/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:12:03 by nicolasbrec       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/07 15:30:16 by nicolasbrec      ###   ########.fr       */
=======
/*   Updated: 2025/06/06 17:25:29 by nicolasbrec      ###   ########.fr       */
>>>>>>> d777815 (add)
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
    // free_before_execve(g);
	if (execve(path, args, g->env) == -1)
	{
		free(path);
		exit_free(g, "Execve", -1, 1);
	}
}

int exec_cmd(t_global *g, t_cmds *cmds)
{
	pid_t	pid;
	int		status;
	char	*pathname;

    if (!handle_expand(g, cmds))
        return (0);
    printf("cmds = %p\n", cmds);
    printf("cmd = %p\n", cmds->topcmd);
	pathname = get_cmd_path(g, cmds->topcmd);
	g->tmp.cmd_arg = get_cmds_in_tab(g, cmds->topcmd);
	if (check_builtin(g, cmds, g->tmp.cmd_arg))
		return (0);
	pid = handle_error_fork(g, fork(), NULL);
	if (pid == 0)
		exec_cmd_fork(g, cmds, pathname, g->tmp.cmd_arg);
	free(pathname);
	free_tabstr(g->tmp.cmd_arg);
	waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}
