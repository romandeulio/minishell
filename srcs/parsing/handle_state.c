/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:21:52 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/16 17:51:16 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int   len_word(char *word, char separator)
{
    int i;

    i = 0;
    while (word[i] != separator)
        i++;
    return (i);
}

int    handle_dq_state(char *word, t_global *g)
{
    int i;
    char *new;

    i = 0;
    while (word[i] != '\"')
        i++;
    new_node
    return (i);
}

int   handle_normal_state(char *word, t_global *g)
{
    int i;

    i = 0;
    while (word[i] != ' ')
        i++;
    return (i);
}
