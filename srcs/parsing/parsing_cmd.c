/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:35:48 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/16 17:45:28 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int count_word(char *word, t_global *g)
{
    int i;

    i = 0;
    while (word[i] == ' ')
        i++;
    if (word[i] == '\'')
        return (handle_sq_state(&word, g));
    else if (word[i] == '\"')
        return (handle_dq_state(word[i], g));
    else
        return (handle_normal_state(word, g));
}

void    parsing_cmd(t_global *g)
{
    int i;
    int j;
    char *word;

    i = 0;
    j = 0;
    while (g->rd.line[i])
    {
        word = malloc(sizeof(char) * count_word(&g->rd.line[i], g) + 1);
        while (g->rd.line[i] == ' ')
            i++;
        if (g->rd.line[i] == '\'')
            handle_sq_state
    }
}
