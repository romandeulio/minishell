/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:21:59 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/16 16:37:39 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(t_global *g)
{
	parsing_cmd(g);
}

void	minishell(t_global *g)
{
	while (1)
	{
		g->rd.line = readline(get_cur_dir(g));
		if (!g->rd.line)
			ft_exit("Readline Error", g);
		else
		{
			check_and_add_history(g->rd.line);
			parsing(g);
		}
		free(g->rd.line);
		free(g->rd.cur_dir);
	}
}

int main(int ac, char **av, char **env)
{
	t_global g;
	(void)av;
	
	if (ac != 1)
	{
		ft_putendl_fd("Usage: ./minishell", 2);
		return (1);
	}
	ft_bzero(&g, sizeof(t_global));
	g.env = env;
	minishell(&g);
	return (0);
}
