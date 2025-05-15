/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:21:59 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/15 15:31:28 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(t_global *g);

void	minishell(t_global *g);

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
	while (1)
	{
		parsing(&g);
		minishell(&g);
	}
	return (0);
}
