/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:30:34 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/12 16:23:15 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	lenword_after_expand(char *subword)
{
	int	i;

	i = 0;
	while (subword[i] != ' ')
		i++;
	return (i);
}

t_subcmd	*separate_subcmd(t_global *g, t_subcmd *subcmd)
{
	t_subcmd	*new;
	t_subcmd	*last;
	int			i;
	int			start;

	new = NULL;
	i = 0;
	while (subcmd->state == NORMAL && subcmd->subword[i])
	{
		while (subcmd->subword[i] == ' ')
			i++;
		if (!subcmd->subword[i])
			break;
		start = i;
		while (subcmd->subword[i] && subcmd->subword[i] != ' ')
			i++;
		lstadd_back_subcmd(&new, lstnew_nd_subcmd(g, i - start));
		last = lstget_last_nd_subcmd(new);
		ft_strncpy(last->subword, &subcmd->subword[start], i - start);
		last->subword[i - start] = '\0';
		last->state = subcmd->state;
	}
	return (new);
}
