/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:35:13 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/01 22:59:12 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_ch_after_dollar(char *c)
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

	expand_key = malloc(sizeof(char) * (count_expand_key(subword[i])));
	if (!expand_key)
		ft_exit(g, "Malloc", -1, 1); // verif les autres trucs a free
	i = 0;
	while (check_ch_after_dollar(subword[i]))
	{
		expand_key[i] = subword[i];
		i++;
	}
	expand_key[i] = '\0';
	return (expand_key);
}

int	cnt_expand_subw(t_global *g, char *subword)
{
	int		count;
	char	*expand_key;
	char	*expand_value;

	count = 0;
	while (*subword)
	{
		if (*subword == '$' && *(subword + 1))
		{
			expand_key = get_expand_key(g, (subword + 1));
			expand_value = getenv(expand_key);
			if (*(subword + 1) == '?')
				count += ft_strlen(ft_itoa(g->exit_code));
			else if (expand_value && !ft_isalnum(*(subword + 1)))
				count += ft_strlen(expand_value);
			else if (!expand_value && !ft_isalnum(*(subword + 1)))
				count += 1;
			subword += ft_strlen(expand_key) + 1;
			free(expand_key);
			continue ;
		}
		subword++;
		count++;
	}
	return (count);
}

int	expand_dollars(t_global *g, char *subw, char *new_subw, int *i_newsubw)
{
	int		count;
	char	*expand_key;
	char	*expand_value;

	expand_key = get_expand_key(g, &subw[1]);
	expand_value = getenv(expand_key);
	if (subw[1] == '?')
	{
		ft_strcpy(&new_subw, ft_itoa(g->exit_code));
		*i_newsubw += ft_strlen(ft_itoa(g->exit_code));
	}
	else if (expand_value && !ft_isalnum(subw[1]))
	{
		ft_strcpy(&new_subw, expand_value);
		*i_newsubw += ft_strlen(expand_value);
	}
	else if (!expand_value && !ft_isalnum(subw[1]))
	{
		ft_strcpy(&new_subw, "$");
		(*i_newsubw)++;
	}
	count = ft_strlen(expand_key) + 1;
	free(expand_key);
	return (count);
}

void new_subw_expand(t_global *g, t_subtok *subtok)
{
	int		i;
	int		j;
	char	*new_subword;
	char	*subword;

	subword = subtok->subword;
	new_subword = malloc(sizeof(char) * (cnt_expand_subw(g, subword) + 1));
	i = 0;
	j = 0;
	while (subword[i])
	{
		if (subword[i] == '$' && subword[i + 1])
			i += expand_dollars(g, &subword[i], &new_subword[j], &j);
		else
			new_subword[j++] = subword[i++];
	}
	free(subtok->subword);
	subtok->subword = new_subword;
}

void	handle_expand(t_global *g)
{
	t_tok_stk	*stk;
	t_tok_nd	*tok_nd;
	t_subtok	*subtok;
	t_subtok	*tmp;

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
				if (!subtok->subword[0])
				{
					tmp = subtok;
					subtok = subtok->next;
					lstdelete_subtok(&tok_nd->top, tmp);
				}
			}
			subtok = subtok->next;
		}
		tok_nd = tok_nd->next;
	}
}
