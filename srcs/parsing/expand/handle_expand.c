/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:35:13 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/13 18:36:47 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*get_expand_key(t_global *g, char *subword)
{
	int		i;
	char	*expand_key;

	expand_key = malloc(sizeof(char) * (count_expand_key(subword) + 1));
	if (!expand_key)
		exit_free(g, "Malloc", -1, 1);
	i = 0;
	while (check_ch_after_dollar(subword[i]))
	{
		expand_key[i] = subword[i];
		i++;
	}
	expand_key[i] = '\0';
	return (expand_key);
}

char	*get_var_value(t_global *g, char *key)
{
	int		i;
	char	**env;
	size_t	key_len;

	i = 0;
	env = g->env;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	expand_dollars(t_global *g, char *subw, char *new_subw, int *idx_newsubw)
{
	int		count;
	char	*expand_key;
	char	*expand_value;

	expand_key = get_expand_key(g, &subw[1]);
	expand_value = get_var_value(g, expand_key);
	count = ft_strlen(expand_key) + 1;
	if (subw[1] == '?')
	{
		ft_strcpy(new_subw, ft_itoa(g_exit_code));
		*idx_newsubw += ft_strlen(ft_itoa(g_exit_code));
		count = 2;
	}
	else if (ft_isdigit((int)subw[1]))
		count = 2;
	else if (expand_value)
	{
		ft_strcpy(new_subw, expand_value);
		*idx_newsubw += ft_strlen(expand_value);
	}
	free(expand_key);
	return (count);
}

void	new_subw_expand(t_global *g, t_subcmd *subcmd)
{
	int		i;
	int		j;
	char	*new_subw;
	char	*subw;

	subw = subcmd->subword;
	new_subw = malloc(sizeof(char) * (cnt_new_subw_expand(g, subw) + 1));
	i = 0;
	j = 0;
	while (subw[i])
	{
		if (subw[i] == '$' && subw[i + 1])
		{
			if (is_expandable_dollar(subw[i + 1]))
				i += expand_dollars(g, &subw[i], &new_subw[j], &j);
			else
				new_subw[j++] = subw[i++];
		}
		else
			new_subw[j++] = subw[i++];
	}
	new_subw[j] = '\0';
	free(subcmd->subword);
	subcmd->subword = new_subw;
}
