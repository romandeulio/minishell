/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:06:55 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/19 00:19:19 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_cur_dir(t_global *g)
{
    char *path_abs;
    char *name_cur_dir;
    
    path_abs = getcwd(NULL, 0);
    name_cur_dir = ft_strrchr(path_abs, '/');
    g->rd.cur_dir = ft_strjoin(&name_cur_dir[1], "$ ");
    free(path_abs);
    if (!g->rd.cur_dir)
        ft_exit("Malloc", g);
    return (g->rd.cur_dir);
}
