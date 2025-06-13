/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:35:18 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/13 21:46:43 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_pwd(void)
{
    char    *path;

    path = getcwd(NULL, 0);
    if (!path)
    {
        perror("pwd");
        g_exit_code = 1;
        return ;
    }
    ft_putendl_fd(path, 1);
    free(path);
    g_exit_code = 0;
}
