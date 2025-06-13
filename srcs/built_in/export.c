/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:50:17 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/13 13:42:57 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_global *g, char **cmd)
{
	if (!cmd_is_valid(cmd[1]))
	{
		ft_putendl_fd("export: not a valid identifier", 2);
		g_exit_code = 1;
		return ;
	}
	env_add(g, cmd[1]);
}

int	cmd_is_valid(char *cmd)
{
	int	i;

	if (!cmd || (!ft_isalpha(cmd[0]) && cmd[0] != '_'))
		return (0);
	i = 1;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	env_add(t_global *g, char *cmd)
{
	int		i;
	char	**new_env;
	char	*var;

	i = 0;
	var = find_var(cmd);
	while (g->env[i] && ft_strncmp(g->env[i], var, ft_strlen(var)))
		i++;
	free(var);
	if (g->env[i])
	{
		free(g->env[i]);
		g->env[i] = ft_strdup(cmd);
	}
	else
	{
		new_env = env_cpy(g, g->env, tab_size(g->env) + 1);
		new_env[tab_size(g->env)] = ft_strdup(cmd);
		new_env[tab_size(g->env) + 1] = NULL;
		free_tabstr(g->env);
		g->env = new_env;
	}
}

char	*find_var(char *cmd)
{
	int		i;
	char	*cmd_dup;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	cmd_dup = ft_strndup(cmd, i + 1);
	return (cmd_dup);
}
