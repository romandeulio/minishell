/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:51:52 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 19:07:51 by nbrecque         ###   ########.fr       */
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

int	check_dollar_alone(t_subcmd *subcmd)
{
	if (!ft_strcmp(subcmd->subword, "$") && subcmd->state == NORMAL
		&& subcmd->next)
	{
		free(subcmd->subword);
		subcmd->subword = ft_strdup("");
		return (1);
	}
	return (0);
}
