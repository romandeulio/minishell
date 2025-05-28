/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_subword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:39:00 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/28 12:43:23 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	count_join_subword(t_subtok *subtok)
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

char	*join_subword(t_global *g, t_subtok *subtok)
{
	char	*allword;
	char	*tmp;

	allword = malloc(sizeof(char) * (count_join_subword(subtok) + 1));
	if (!allword)
		ft_exit("Malloc", g);
	allword = NULL;
	tmp = ft_strdup("");
	while (subtok)
	{
		allword = ft_strjoin(tmp, subtok->subword);
		free(tmp);
		tmp = allword;
		subtok = subtok->next;
	}
	return (allword);
}
