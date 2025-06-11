/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_subword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:39:00 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/11 01:58:48 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	count_join_subw_subtok(t_subtok *subtok)
{
	int	count;

	count = 0;
	while (subtok)
	{
		count += ft_strlen(subtok->subword);
		subtok = subtok->next;
	}
	return (count);
}

char	*join_subw_subtok(t_global *g, t_subtok *subtok)
{
	char	*allword;
	char	*tmp;

	allword = malloc(sizeof(char) * (count_join_subw_subtok(subtok) + 1));
	if (!allword)
		exit_free(g, "Malloc", -1, 1);
	allword = NULL;
	tmp = NULL;
	while (subtok)
	{
		allword = ft_strjoin(tmp, subtok->subword);
		free(tmp);
		tmp = allword;
		subtok = subtok->next;
	}
	return (allword);
}

int	count_join_subw_subcmd(t_subcmd *subcmd)
{
	int	count;

	count = 0;
	while (subcmd)
	{
		count += ft_strlen(subcmd->subword);
		subcmd = subcmd->next;
	}
	return (count);
}

char	*join_subw_subcmd(t_global *g, t_subcmd *subcmd)
{
	char	*allword;
	char	*tmp;

	allword = malloc(sizeof(char) * (count_join_subw_subcmd(subcmd) + 1));
	if (!allword)
		exit_free(g, "Malloc", -1, 1);
	allword = NULL;
	tmp = NULL;
	while (subcmd)
	{
		allword = ft_strjoin(tmp, subcmd->subword);
		free(tmp);
		tmp = allword;
		subcmd = subcmd->next;
	}
	return (allword);
}
