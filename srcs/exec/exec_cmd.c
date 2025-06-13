/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:12:03 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:33:38 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_perm(t_global *g, struct stat file_info, int stat_error,
		char *cmd)
{
	if (stat_error == 0 && S_ISDIR(file_info.st_mode))
	{
		ft_printf("minishell: %s", cmd);
		exit_free(g, " Is a directory", 2, 126);
	}
	else if (stat_error == 0 && !(file_info.st_mode & S_IXUSR))
	{
		ft_printf("minishell: %s", cmd);
		exit_free(g, " Permission denied", 2, 126);
	}
	else if (stat_error != 0)
	{
		ft_printf("minishell: %s", cmd);
		exit_free(g, " No such file or directory", 2, 127);
	}
}

void	exec_cmd_fork(t_global *g, t_cmds *cmds, char *path)
{
	struct stat	file_info;
	int			stat_error;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!exec_cmdfile(g, cmds))
		exit_free(g, NULL, 2, 1);
	if (execve(path, g->tmp.cmd_arg, g->env) == -1)
	{
		stat_error = stat(path, &file_info);
		if (!ft_strncmp(path, "./", 2) || !ft_strncmp(path, "/", 1)
			|| !ft_strncmp(path, "../", 3))
		{
			free(path);
			check_perm(g, file_info, stat_error, g->tmp.cmd_arg[0]);
		}
		free(path);
		ft_putstr_fd("minishell:", 1);
		exit_free(g, " command not found", 2, 127);
	}
}

int	prepare_exec_cmd(t_global *g, t_cmds *cmds, char *path)
{
	pid_t	pid;
	int		status;

	pid = handle_error_fork(g, fork(), NULL);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		exec_cmd_fork(g, cmds, path);
	free(path);
	free_tabstr(g->tmp.cmd_arg);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (WEXITSTATUS(status));
}

int	exec_cmd(t_global *g, t_cmds *cmds)
{
	int		code;
	char	*pathname;

	if (cmds->topcmd && !handle_expand_cmd(g, cmds))
		return (0);
	handle_wildcard_cmd(g, cmds);
	g->tmp.cmd_arg = get_cmds_in_tab(g, cmds->topcmd);
	if (is_builtin(g->tmp.cmd_arg))
	{
		code = check_builtin(g, cmds, g->tmp.cmd_arg);
		free_tabstr(g->tmp.cmd_arg);
		return (code);
	}
	pathname = get_cmd_path(g, cmds->topcmd);
	return (prepare_exec_cmd(g, cmds, pathname));
}
