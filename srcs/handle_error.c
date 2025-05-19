/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:20:31 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/19 00:19:21 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void write_error_syntax(char *token)
{
    write(2, "minishell: syntax error near unexpected token `", 47);
    write(2, token, ft_strlen(token));
    write(2, "'\n", 2);
}
