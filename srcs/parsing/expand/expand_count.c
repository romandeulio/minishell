/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:13:52 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/06 13:18:59 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	count_expand_key(char *subword)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (subword[i])
	{
		if (!check_ch_after_dollar(subword[i]))
			break ;
		i++;
		count++;
	}
	return (count);
}

int	cnt_expand_dollar(t_global *g, char *subword, int *count)
{
	int		i;
	char	*expand_key;
	char	*expand_value;

	expand_key = get_expand_key(g, (subword + 1));
	expand_value = getenv(expand_key);
	i = ft_strlen(expand_key) + 1;
	if (subword[i + 1] == '?')
	{
		*count += ft_strlen(ft_itoa(g->exit_code));
		i = 2;
	}
	else if (ft_isdigit((int)subword[i + 1]))
		i = 2;
	else if (expand_value)
		*count += ft_strlen(expand_value);
	free(expand_key);
	return (i);
}

int	cnt_new_subw_expand(t_global *g, char *subword)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (subword[i])
	{
		if (subword[i] == '$' && subword[i + 1])
			i += cnt_expand_dollar(g, &subword[i], &count);
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}
