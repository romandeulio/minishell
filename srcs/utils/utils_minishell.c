/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:09:53 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/15 18:33:21 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_env(t_global *g, char **env)
{
	if (!*env || !env)
	{
		g->env = malloc(sizeof(char *) * 2);
		g->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		g->env[1] = NULL;
	}
	else
		g->env = env_cpy(g, env, tab_size(env));
}

char	*ft_getenv(char **env, char *to_find)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], to_find, ft_strlen(to_find)))
			return (env[i]);
		i++;
	}
	return (NULL);
}
