/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:10 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/13 21:51:38 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	int	no_nl;

	i = 1;
	no_nl = 0;
	while (cmd[i] && !ft_strcmp(cmd[i], "-n") && cmd[i][2] == '\0')
	{
		no_nl = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], 1);
		if (cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if (!no_nl)
		ft_putchar_fd('\n', 1);
	g_exit_code = 0;
}
