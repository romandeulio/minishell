/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:06:55 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/10 11:19:58 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cur_dir(t_global *g)
{
	char	*path_abs;
	char	*name_cur_dir;

	path_abs = getcwd(NULL, 0);
	name_cur_dir = ft_strrchr(path_abs, '/');
	g->rd.cur_dir = ft_strjoin(&name_cur_dir[1], "$ ");
	free(path_abs);
	if (!g->rd.cur_dir)
		exit_free(g, "Malloc", -1, 1);
	return (g->rd.cur_dir);
}
