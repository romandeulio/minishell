/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:27:35 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 14:49:29 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char **cmd_arg)
{
	if (!cmd_arg)
		return (0);
	if (!ft_strcmp("cd", cmd_arg[0]))
		return (1);
	if (!ft_strcmp("echo", cmd_arg[0]))
		return (1);
	else if (!ft_strcmp("env", cmd_arg[0]))
		return (1);
	else if (!ft_strcmp("exit", cmd_arg[0]))
		return (1);
	else if (!ft_strcmp("export", cmd_arg[0]))
		return (1);
	else if (!ft_strcmp("pwd", cmd_arg[0]))
		return (1);
	else if (!ft_strcmp("unset", cmd_arg[0]))
		return (1);
	else
		return (0);
}

void	save_std(t_global *g)
{
	g->tmp.save_stdin = dup(STDIN_FILENO);
	g->tmp.save_stdout = dup(STDOUT_FILENO);
}

void	restore_std(t_global *g)
{
	dup2(g->tmp.save_stdin, STDIN_FILENO);
	dup2(g->tmp.save_stdout, STDOUT_FILENO);
	close(g->tmp.save_stdin);
	close(g->tmp.save_stdout);
}

int	check_builtin(t_global *g, t_cmds *cmds, char **cmd_arg)
{
	save_std(g);
	if (!exec_cmdfile(g, cmds))
		return (1);
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
	restore_std(g);
	return (g_exit_code);
}
