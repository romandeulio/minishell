/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:50:39 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/15 18:43:38 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_global *g, char **cmd)
{
	env_remove(g, cmd[1]);
}

void	env_remove(t_global *g, char *cmd)
{
	int		i;
	int		j;
	int		to_free;
	char	**new_env;

	to_free = find_path(g->env, cmd);
	if (to_free == -1)
		return ;
	new_env = malloc(sizeof(char *) * tab_size(g->env));
	if (!new_env)
		exit_free(g, "Malloc", -1, 1);
	i = 0;
	j = 0;
	while (g->env[j])
	{
		if (to_free != j)
			new_env[i++] = ft_strdup(g->env[j]);
		j++;
	}
	new_env[i] = NULL;
	free_tabstr(g->env);
	g->env = new_env;
	g_exit_code = 0;
}
