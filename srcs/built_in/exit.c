/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:51:04 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/04 20:00:20 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_global *g, char **cmd)
{
	if (!cmd[1])
		exit_free(g, "exit", 1, g->exit_code);
	else
	{
		if (tab_size(cmd) == 2)
		{
			if (is_num_str(cmd[1]))
				exit_free(g, "exit", 1, ft_atoi(cmd[1]));
			else
			{
				ft_printf("exit: %s: numeric argument required\n", cmd[1]);
				exit_free(g, NULL, 2, 2);
			}
		}
		else
		{
			g->exit_code = 1;
			ft_putendl_fd("exit", 1);
			ft_putendl_fd("exit: too many arguments", 2);
			return ;
		}
	}
}
