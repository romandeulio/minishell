/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:35:18 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/04 16:23:48 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		return ;
	}
	ft_putendl_fd(path, 1);
	free(path);
}
