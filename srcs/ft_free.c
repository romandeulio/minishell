/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:14:27 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/23 16:37:29 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_and_reset_readline(t_global *g)
{
    free(g->rd.line);
	free(g->rd.cur_dir);
    ft_bzero(&g->rd, sizeof(t_rdline));
}

void	free_and_reset_parsing(t_global *g)
{
	lstfree_tok(&g->tok_stk);
    ft_bzero(&g->tok_stk, sizeof(t_tok_stk));
}
