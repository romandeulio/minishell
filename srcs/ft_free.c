/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:14:27 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/16 17:14:53 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_list(t_parsing *p)
{
    t_node *tmp;

    tmp = p->node;
    while (p->node)
    {
        p->node = p->node->next;
        free(tmp->word);
        free(tmp);
        tmp = p->node;
    }
}
