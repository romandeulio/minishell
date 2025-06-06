/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:35:13 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/06 14:59:22 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*get_expand_key(t_global *g, char *subword)
{
	int		i;
	char	*expand_key;

	expand_key = malloc(sizeof(char) * (count_expand_key(subword) + 1));
	if (!expand_key)
		exit_free(g, "Malloc", -1, 1); // verif les autres trucs a free
	i = 0;
	while (check_ch_after_dollar(subword[i]))
	{
		expand_key[i] = subword[i];
		i++;
	}
	expand_key[i] = '\0';
	return (expand_key);
}

int	expand_dollars(t_global *g, char *subw, char *new_subw, int *idx_newsubw)
{
	int		count;
	char	*expand_key;
	char	*expand_value;

	expand_key = get_expand_key(g, &subw[1]);
	expand_value = getenv(expand_key);
	count = ft_strlen(expand_key) + 1;
	if (subw[1] == '?')
	{
		ft_strcpy(new_subw, ft_itoa(g->exit_code));
		*idx_newsubw += ft_strlen(ft_itoa(g->exit_code));
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

void	new_subw_expand(t_global *g, t_subtok *subtok)
{
	int		i;
	int		j;
	char	*new_subw;
	char	*subw;

	subw = subtok->subword;
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
	free(subtok->subword);
	subtok->subword = new_subw;
}

void	handle_expand(t_global *g)
{
	t_tok_stk	*stk;
	t_tok_nd	*tok_nd;
	t_subtok	*subtok;

	stk = &g->tok_stk;
	tok_nd = stk->top;
	while (tok_nd)
	{
		subtok = tok_nd->top;
		while (subtok)
		{
			if (subtok->varenv)
			{
				if (!check_dollar_alone(subtok))
					new_subw_expand(g, subtok);
				if (handle_dlt_subtok(&tok_nd->top, &subtok))
					continue ;
			}
			subtok = subtok->next;
		}
		if (handle_dlt_tok_nd(&stk->top, &tok_nd))
			continue ;
		tok_nd = tok_nd->next;
	}
}
