/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:51:04 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/10 11:09:01 by rodeulio         ###   ########.fr       */
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
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("exit:", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit_free(g, NULL, 2, 2);
	}
}
