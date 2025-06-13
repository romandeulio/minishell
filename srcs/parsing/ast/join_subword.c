/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_subword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:39:00 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 02:22:00 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*join_subw_subtok(t_global *g, t_subtok *subtok)
{
	char	*allword;
	char	*tmp;

	allword = NULL;
	while (subtok)
	{
		tmp = allword;
		allword = ft_strjoin(tmp, subtok->subword);
		free(tmp);
		if (!allword)
			exit_free(g, "Malloc", -1, 1);
		subtok = subtok->next;
	}
	return (allword);
}

char	*join_subw_subcmd(t_global *g, t_subcmd *subcmd)
{
	char	*allword;
	char	*tmp;

	allword = NULL;
	while (subcmd)
	{
		tmp = allword;
		allword = ft_strjoin(tmp, subcmd->subword);
		free(tmp);
		if (!allword)
			exit_free(g, "Malloc", -1, 1);
		subcmd = subcmd->next;
	}
	return (allword);
}
