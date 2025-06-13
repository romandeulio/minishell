/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:30:41 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:40:23 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	lenpath_wildcard(t_subcmd *subcmd)
{
	int	tmp_count;
	int	real_count;
	int	i;

	tmp_count = 0;
	real_count = 0;
	while (subcmd)
	{
		i = 0;
		while (subcmd->subword[i])
		{
			if (subcmd->subword[i] == '/')
				real_count = tmp_count + 1;
			else if (subcmd->subword[i] == '*' && subcmd->state == NORMAL)
				return (real_count);
			tmp_count++;
			i++;
		}
		subcmd = subcmd->next;
	}
	return (-1);
}

int	len_wildcard(t_subcmd *subcmd, int start)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (subcmd)
	{
		while (subcmd->subword[i])
		{
			if (subcmd->subword[i] == '/')
				return (count);
			count++;
			i++;
		}
		i = 0;
		subcmd = subcmd->next;
	}
	return (count);
}
