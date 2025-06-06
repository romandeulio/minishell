/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:35:13 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/06 12:17:08 by nicolasbrec      ###   ########.fr       */
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
	int		i;
	int		count;

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
	char	*new_subword;
	char	*subword;

	subword = join_subword(g, subtok);
	new_subword = malloc(sizeof(char) * (cnt_new_subw_expand(g, subword) + 1));
	i = 0;
	j = 0;
	while (subword[i])
	{
		if (subword[i] == '$' && subword[i + 1])
		{
			if (is_expandable_dollar(subword[i + 1]))
				i += expand_dollars(g, &subword[i], &new_subword[j], &j);
			else
				new_subword[j++] = subword[i++];
		}
		else
			new_subword[j++] = subword[i++];
	}
	new_subword[j] = '\0';
	free(subtok->subword);
	subtok->subword = new_subword;
}

int	handle_dlt_subtok(t_subtok **top, t_subtok **subtok)
{
	t_subtok	*tmp;

	if (!(*subtok)->subword[0])
	{
		tmp = *subtok;
		*subtok = (*subtok)->next;
		lstdelete_subtok(top, tmp);
		return (1);
	}
	return (0);
}

int	handle_dlt_tok_nd(t_tok_nd **top, t_tok_nd **tok_nd)
{
	t_tok_nd	*tmp;

	if (!(*tok_nd)->top)
	{
		tmp = *tok_nd;
		*tok_nd = (*tok_nd)->next;
		lstdelete_tok_nd(top, tmp);
		return (1);
	}
	return (0);
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
