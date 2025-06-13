/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:12:03 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 02:22:44 by nicolasbrec      ###   ########.fr       */
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

// void	exec_cmd_fork(t_global *g, t_cmds *cmds, char *path, char **args)
// {
// 	exec_cmdfile(g, cmds);
// 	check_pathname(g, path);
// 	errno = 0;
// 	check_perm(g, cmds->file);
// 	if (execve(path, args, g->env) == -1)
// 	{
// 		free(path);
// 		print_error(g);
// 		//print_error(g, cmds->file);
// 	}
// }

void	check_perm(t_global *g, struct stat file_info, int stat_error,
		char *cmd)
{
	if (stat_error == 0 && S_ISDIR(file_info.st_mode))
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(cmd, 1);
		exit_free(g, " Is a directory", 2, 126);
	}
	else if (stat_error == 0 && !(file_info.st_mode & S_IXUSR))
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(cmd, 1);
		exit_free(g, " Permission denied", 2, 126);
	}
	else if (stat_error != 0)
	{
		ft_putstr_fd("minishell:", 1);
		ft_putstr_fd(cmd, 1);
		exit_free(g, " No such file or directory", 2, 127);
	}
}

void	exec_cmd_fork(t_global *g, t_cmds *cmds, char *path, char **args)
{
	struct stat	file_info;
	int			stat_error;

	if (!exec_cmdfile(g, cmds))
		exit_free(g, NULL, 2, 1);
	if (execve(path, args, g->env) == -1)
	{
		stat_error = stat(path, &file_info);
		if (!ft_strncmp(path, "./", 2) || !ft_strncmp(path, "/", 1)
			|| !ft_strncmp(path, "../", 3))
		{
			free(path);
			check_perm(g, file_info, stat_error, args[0]);
		}
		free(path);
		exit_free(g, " command not found", 2, 127);
	}
}

int	exec_cmd(t_global *g, t_cmds *cmds)
{
	int 	code;
	pid_t	pid;
	int		status;
	char	*pathname;

	if (!handle_expand_cmd(g, cmds))
		return (0);
	handle_wildcard_cmd(g, cmds);
	pathname = get_cmd_path(g, cmds->topcmd);
	g->tmp.cmd_arg = get_cmds_in_tab(g, cmds->topcmd);
	if (is_builtin(g->tmp.cmd_arg))
	{
		code = check_builtin(g, cmds, g->tmp.cmd_arg);
		free(pathname);
		free_tabstr(g->tmp.cmd_arg);
		return (code);
	}
	pid = handle_error_fork(g, fork(), NULL);
	if (pid == 0)
		exec_cmd_fork(g, cmds, pathname, g->tmp.cmd_arg);
	free(pathname);
	free_tabstr(g->tmp.cmd_arg);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

