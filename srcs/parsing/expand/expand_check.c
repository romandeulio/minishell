/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:51:52 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/06 13:18:20 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_expandable_dollar(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_' || c == '?');
}

int	check_ch_after_dollar(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}
int	check_dollar_alone(t_subtok *subtok)
{
	if (!ft_strcmp(subtok->subword, "$") && subtok->state == NORMAL
		&& subtok->next)
	{
		free(subtok->subword);
		subtok->subword = ft_strdup("");
		return (1);
	}
	return (0);
}