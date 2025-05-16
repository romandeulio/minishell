/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:14:24 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/16 15:30:25 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_exit(char *msg, t_global *g)
{
    perror(msg);
    free(g->rd.cur_dir);
    exit(1);
}

/* void    ft_free(t_global *g)
{
    if (g)
} */