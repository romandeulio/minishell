/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:20:31 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/28 23:13:18 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_line(t_subtok *subtok, t_global *g)
{
    g->error_line = 1;
    write_syntax_error(subtok);
}

void write_syntax_error(t_subtok *subtok)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    while (subtok)
    {
        ft_putstr_fd(subtok->subword, 2);
        subtok = subtok->next;
    }
    ft_putstr_fd("'\n", 2);
}
