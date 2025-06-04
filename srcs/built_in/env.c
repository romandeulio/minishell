/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:50:55 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/03 21:22:18 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_global *g)
{
	int	i;

	i = 0;
	while (g->env[i])
		ft_putendl_fd(g->env[i++], 1);
}

char	**env_cpy(t_global *g, char **env, int size)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
        exit_free(g, "Malloc", -1, 1);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	env_add(t_global *g, char *cmd)
{
	int		i;
	char	**new_env;
    char *var;

	i = 0;
    var = find_var(cmd);
	while (g->env[i] && ft_strncmp(g->env[i], var, ft_strlen(var)))
		i++;
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

void    env_remove(t_global *g, char *cmd)
{
    int i;
    char **new_env;

    i = 0;
    while(g->env[i])
    {
        if (!ft_strcmp(g->env[i], cmd))
        {
            new_env = malloc(sizeof(char *) * (tab_size(g->env) - 1));
	        if (!new_env)
                exit_free(g, "Malloc", -1, 1);
	        while (g->env[i])
	        {
                if (!ft_strcmp(g->env[i], cmd))
                    i++;
    		    new_env[i] = ft_strdup(g->env[i]);
	    	    i++;
	        }
	        new_env[i] = NULL;
        }
        i++;
    }
}

char *find_var(char *cmd)
{
    int i;
    char *cmd_dup;
    
    i = 0;
    while (cmd[i] && cmd[i] != '=')
        i++;
    cmd_dup = ft_strndup(cmd, i + 1);
    return (cmd_dup);
}