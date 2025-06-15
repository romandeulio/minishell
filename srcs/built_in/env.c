/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:50:55 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/15 18:33:13 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_global *g)
{
	int	i;

	i = 0;
	while (g->env[i])
		ft_putendl_fd(g->env[i++], 1);
	g_exit_code = 0;
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
