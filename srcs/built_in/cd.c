/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:49:33 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/13 17:58:59 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(t_global *g, char **cmd)
{
	int	code;

	if (tab_size(cmd) > 2)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("exit: too many arguments", 2);
		g_exit_code = 1;
		return ;
	}
	code = change_path(g, cmd[1]);
	g_exit_code = code;
	if (!code)
		change_env(g);
}

int	change_path(t_global *g, char *cmd)
{
	char	*path;

	if (!cmd)
	{
		path = ft_getenv(g->env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else
		path = cmd;
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

void	change_env(t_global *g)
{
	int		pwd;
	int		oldpwd;
	char	*path;

	pwd = find_path(g->env, "PWD=");
	oldpwd = find_path(g->env, "OLDPWD=");
	if (pwd == -1 || oldpwd == -1)
        exit_free(g, "cd", -1, 1);
	path = getcwd(NULL, 0);
	free(g->env[oldpwd]);
	g->env[oldpwd] = ft_strjoin("OLDPWD=", g->env[pwd] + 4);
	free(g->env[pwd]);
	g->env[pwd] = ft_strjoin("PWD=", path);
	free(path);
}

int	find_path(char **env, char *to_find)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(to_find, env[i], ft_strlen(to_find)))
			return (i);
		i++;
	}
	return (-1);
}
