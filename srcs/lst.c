/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:58:25 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/16 17:08:58 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node *new_node(char *word, t_global *g)
{
    t_node *new;

    new = malloc(sizeof(t_node));
    if (!new)
        ft_exit("Malloc error", g);
    new->word = word;
    new->next = NULL;
    return (new);
}
