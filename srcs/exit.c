/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:14:24 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/19 00:43:20 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_exit(char *msg, t_global *g)
{
    if (msg)
        perror(msg);
    free(g->rd.cur_dir);
    lstfree_token(&g->tok_stk);
    exit(1);
}
