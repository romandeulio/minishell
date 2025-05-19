/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:45:49 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/19 00:22:21 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    check_and_add_history(char *str)
{
    int i;
    
    i = 0;
    while (str[i] == ' ')
        i++;
    if (str[i])
        add_history(str);
}
