/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:45:06 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/13 18:46:42 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	increment_to_first_slash(t_subcmd **subcmd, int *start)
{
	int	i;

	i = *start;
	while (*subcmd)
	{
		while ((*subcmd)->subword[i])
		{
			if ((*subcmd)->subword[i] == '/')
			{
				*start = i;
				return ;
			}
			i++;
		}
		i = 0;
		*subcmd = (*subcmd)->next;
	}
}

int	subword_len(t_subcmd *subcmd, int start)
{
	int	i;

	i = 0;
	while (subcmd->subword[start])
	{
		start++;
		i++;
	}
	return (i);
}

int	check_is_wildcard(t_subcmd *subcmd)
{
	int	i;

	if (subcmd->state != NORMAL)
		return (0);
	i = 0;
	while (subcmd->subword[i])
	{
		if (subcmd->subword[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
