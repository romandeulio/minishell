/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:14:27 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/01 16:06:42 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_and_reset_readline(t_global *g)
{
    free(g->rd.line);
    free(g->rd.full_line);
	free(g->rd.cur_dir);
    ft_bzero(&g->rd, sizeof(t_rdline));
}

void	free_and_reset_parsing(t_global *g)
{
	lstfree_tok(&g->tok_stk);
    ft_bzero(&g->tok_stk, sizeof(t_tok_stk));
    free_ast(g->ast);
    g->ast = NULL;
}

void reinit_new_line(t_global *g)
{
	free_and_reset_readline(g);
	free_and_reset_parsing(g);
	g->error_line = 0;
}
