/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:20:31 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/01 16:07:33 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void write_syntax_error(t_global *g, t_subtok *subtok)
{
	g->error_line = 1;
	g->exit_code = 2;
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    while (subtok)
    {
        ft_putstr_fd(subtok->subword, 2);
        subtok = subtok->next;
    }
    ft_putstr_fd("'\n", 2);
}
