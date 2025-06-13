/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:06:55 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/13 21:50:18 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_path_abs(t_global *g)
{
	char	*pwd;
	char	*tmp;
	char	*result;
	char	*last_slash;

	pwd = get_var_value(g, "PWD");
	if (!pwd)
		return (ft_strdup("$ "));
	tmp = ft_strjoin(pwd, "$ ");
	last_slash = ft_strrchr(tmp, '/');
	if (last_slash)
		result = ft_strdup(last_slash + 1);
	else
		result = ft_strdup(tmp);
	free(tmp);
	return (result);
}

char	*get_cur_dir(t_global *g)
{
	char	*path_abs;
	char	*name_cur_dir;

	path_abs = getcwd(NULL, 0);
	if (!path_abs)
		return (check_path_abs(g));
	name_cur_dir = ft_strrchr(path_abs, '/');
	g->rd.cur_dir = ft_strjoin(&name_cur_dir[1], "$ ");
	free(path_abs);
	if (!g->rd.cur_dir)
		exit_free(g, "Malloc", -1, 1);
	return (g->rd.cur_dir);
}
