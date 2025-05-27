/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:14:24 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/27 17:42:01 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_readline(t_global *g)
{
    free(g->rd.cur_dir);
    free(g->rd.line);
    free(g->rd.full_line);
}

void    ft_exit(char *msg, t_global *g)
{
    if (msg)
        perror(msg);
    free_readline(g);
    lstfree_tok(&g->tok_stk);
    // free l'arbre ast (chaque nd de l'ast, chaque t_cmds, ..
    // .. chaque nd de t_cmd, et chaque file dans infile et outile)
    exit(1);
}
