/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:35:48 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/16 16:50:58 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    parsing_cmd(t_global *g)
{
    int i;
    int w;
    int j;
    char *tmp;

    i = 0;
    w = 0;
    j = 0;
    while (g->rd.line[i])
    {
        while (g->rd.line[i] != ' ')
        {
            tmp = malloc(i + 1);
            tmp = 
            g->parsing.word[w][j] = ft_strjoin(g->parsing.word[w], tmp);
        }
    }
}
