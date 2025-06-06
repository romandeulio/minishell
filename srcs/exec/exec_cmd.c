/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:12:03 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/06 14:36:37 by rodeulio         ###   ########.fr       */
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

	path_line = get_path_line(g, "PATH=");
	all_path = ft_split(path_line, ':');
	// verif l'echec NULL
	slash_cmd = ft_strjoin("/", join_subword(g, top->subtok));
	// verif l'echec NULL
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

// int	exec_cmd_fork(t_global *g, t_cmds *cmds)
// {
// 	pid_t	pid;

// 	pid = handle_error_fork(g, fork(), NULL);
// }

// void	handle_in_redir(t_global *g, char *file)
// {
// 	int	fd;

// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 		ft_exit(g, "Open", -1, 1);
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// }

// void	handle_out_redir(t_global *g, char *file)
// {
// 	int	fd;

// 	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		ft_exit(g, "Open", -1, 1);
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// }

// void	handle_append_redir(t_global *g, char *file)
// {
// 	int	fd;

// 	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		ft_exit(g, "Open", -1, 1); // voir les autres variable a free
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// }

// int	exec_cmdfile(t_global *g, t_cmds *cmds)
// {
// 	int	fd;

// 	if (cmds->file)
// 	{
// 		if (cmds->redir == IN_REDIR)
// 			handle_in_redir(g, cmds->file);
// 		else if (cmds->redir == OUT_REDIR)
// 			handle_out_redir(g, cmds->file);
// 		else if (cmds->redir == HERE_DOC)
// 			handle_heredoc_redir(g, cmds->file);
// 		else if (cmds->redir == APPEND)
// 			handle_append_redir(g, cmds->file);
// 	}
// }

int	exec_cmd(t_global *g, t_cmds *cmds)
{
	// char	*pathname;
	// pathname = get_cmd_path(g, cmds->topcmd);
	g->tmp.cmd_arg = get_cmds_in_tab(g, cmds->topcmd);
	if (!ft_strcmp("cd", g->tmp.cmd_arg[0]))
		ft_cd(g, g->tmp.cmd_arg);
	if (!ft_strcmp("echo", g->tmp.cmd_arg[0]))
		ft_echo(g->tmp.cmd_arg);
	else if (!ft_strcmp("env", g->tmp.cmd_arg[0]))
		ft_env(g);
	else if (!ft_strcmp("exit", g->tmp.cmd_arg[0]))
		ft_exit(g, g->tmp.cmd_arg);
	else if (!ft_strcmp("export", g->tmp.cmd_arg[0]))
		ft_export(g, g->tmp.cmd_arg);
	else if (!ft_strcmp("pwd", g->tmp.cmd_arg[0]))
		ft_pwd();
	else if (!ft_strcmp("unset", g->tmp.cmd_arg[0]))
		ft_unset(g, g->tmp.cmd_arg);
	return (0);
	/*if (execve(pathname,g->tmp.cmd_arg, g->env) == -1)
	{
		free(pathname);
		free_tabstr(cmd_arg);
		exit_free(g, "Execve", -1 , 1); // Rajoutez ce qu'il y a à free.
	}*/
}
