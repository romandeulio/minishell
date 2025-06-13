/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrecque <nbrecque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:16:10 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/13 18:40:56 by nbrecque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// void	lstjoin_subcmd(t_subcmd **lst1, t_subcmd *lst2)
// {
// 	t_subcmd	*tmp_top;

// 	if (!*lst1)
// 	{
// 		*lst1 = lst2;
// 		return ;
// 	}
// 	tmp_top = *lst1;
// 	while ((*lst1)->next)
// 		*lst1 = (*lst1)->next;
// 	(*lst1)->next = lst2;
// 	*lst1 = tmp_top;
// }

char	*file_full_path(t_global *g, t_subcmd **subcmd, int *idx, int pathlen)
{
	int		j;
	char	*full_path;
	char	*subw;

	j = 0;
	full_path = malloc(sizeof(char) * (pathlen + 1));
	if (!full_path)
		exit_free(g, "Malloc", -1, 1);
	while (j < pathlen)
	{
		*idx = 0;
		subw = (*subcmd)->subword;
		while (subw[*idx] && j < pathlen)
			full_path[j++] = subw[(*idx)++];
		if (j >= pathlen)
			break ;
		*subcmd = (*subcmd)->next;
	}
	full_path[j] = '\0';
	return (full_path);
}

void	increment_to_first_slash(t_subcmd **subcmd, int *start)
{
	int	i;

	i = *start;
	while (*subcmd)
	{
		while ((*subcmd)->subword[i])
		{
			if ((*subcmd)->subword[i] == '/')
			{
				*start = i;
				return ;
			}
			i++;
		}
		i = 0;
		*subcmd = (*subcmd)->next;
	}
}

int	subword_len(t_subcmd *subcmd, int start)
{
	int	i;

	i = 0;
	while (subcmd->subword[start])
	{
		start++;
		i++;
	}
	return (i);
}

int	check_is_wildcard(t_subcmd *subcmd)
{
	int	i;

	if (subcmd->state != NORMAL)
		return (0);
	i = 0;
	while (subcmd->subword[i])
	{
		if (subcmd->subword[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

t_subcmd	*get_rest_in_subcmd(t_global *g, t_subcmd *subcmd, int start)
{
	int			i;
	int			j;
	t_subcmd	*new;
	t_subcmd	*last;

	new = NULL;
	increment_to_first_slash(&subcmd, &start);
	i = start;
	while (subcmd)
	{
		j = 0;
		lstadd_back_subcmd(&new, lstnew_nd_subcmd(g, subword_len(subcmd, i)));
		last = lstget_last_nd_subcmd(new);
		while (subcmd->subword[i])
			last->subword[j++] = subcmd->subword[i++];
		last->subword[j] = '\0';
		last->state = subcmd->state;
		last->varenv = subcmd->varenv;
		last->wildcard = check_is_wildcard(last);
		i = 0;
		subcmd = subcmd->next;
	}
	return (new);
}

char	*get_wildcard_word(t_global *g, t_subcmd *subcmd, int start, char *path)
{
	char	*wildcard_word;
	int		wildcard_len;
	int		i;
	int		j;

	i = start;
	wildcard_len = len_wildcard(subcmd, i);
	wildcard_word = malloc(sizeof(char) * (wildcard_len + 1));
	if (!wildcard_word)
	{
		free(path);
		exit_free(g, "Malloc", -1, 1);
	}
	j = 0;
	while (j < wildcard_len)
	{
		while (subcmd->subword[i] && j < wildcard_len)
			wildcard_word[j++] = subcmd->subword[i++];
		i = 0;
		subcmd = subcmd->next;
	}
	wildcard_word[j] = '\0';
	return (wildcard_word);
}
