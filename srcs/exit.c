/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:14:24 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/03 21:17:20 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_readline(t_global *g)
{
    free(g->rd.cur_dir);
    free(g->rd.line);
    free(g->rd.full_line);
}

void    exit_free(t_global *g, char *msg, int fd, int n_exit)
{
    if (msg && fd > 0)
        ft_putendl_fd(msg, fd);	
    else if (msg && fd == -1)
        perror(msg);
    lstfree_tok(&g->tok_stk);
    free_ast(g->ast);
    free_readline(g);
    rl_clear_history();
    exit(n_exit);
}
