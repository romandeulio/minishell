/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:09:53 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/10 17:30:34 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_error(t_global *g)
{
	if (errno == ENOENT)
			exit_free(g, "Execve", -1, 127);
	else if (errno == EISDIR || errno == EACCES)
			exit_free(g, "Execve", -1, 126);
	else
			exit_free(g, "Execve", -1, 1);
}