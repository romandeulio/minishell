/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:51:04 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/05 15:29:50 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_global *g, char **cmd)
{
	if (!cmd[1])
		exit_free(g, "exit", 1, g->exit_code);
	else if (is_num_str(cmd[1]) && tab_size(cmd) == 2)
		exit_free(g, "exit", 1, ft_atoi(cmd[1]));
	else if (tab_size(cmd) > 2 && is_num_str(cmd[1]))
	{
		g->exit_code = 1;
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("exit: too many arguments", 2);
		return ;
	}
	else
	{
		ft_printf("exit: %s: numeric argument required\n", cmd[1]);
		exit_free(g, NULL, 2, 2);
	}
}
