/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:16:10 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/11 15:34:20 by nicolasbrec      ###   ########.fr       */
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

int check_is_wildcard(t_subcmd *subcmd)
{
	int i;

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

void	join_subcmd_in_allcmd(t_cmd *cmd, t_subcmd *rest)
{
	t_subcmd	*subcmd;

	while (cmd)
	{
		subcmd = cmd->subcmd;
		while (subcmd && subcmd->next)
			subcmd = subcmd->next;
		subcmd->next = rest;
		cmd = cmd->next;
	}
}

void	lstswap_cmd(t_cmd **top, t_cmd *n1, t_cmd *n2)
{
	t_cmd	*cur;
	t_cmd	*prev;

	if (!top || !*top || !n1 || !n2 || n1->next != n2)
		return ;
	cur = *top;
	prev = NULL;
	while (cur)
	{
		if (cur == n1)
		{
			if (!prev)
				*top = n2;
			else
				prev->next = n2;
			n1->next = n2->next;
			n2->next = n1;
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	lstsort_cmd(t_cmd **top)
{
	int		swapped;
	t_cmd	*cur;
	char *a;
	char *b;

	if (!top || !*top)
		return ;
	swapped = 1;
	while (swapped)
	{
		cur = *top;
		swapped = 0;
		while (cur && cur->next)
		{
			a = cur->subcmd->subword;
			b = cur->next->subcmd->subword;
			if (a && b && ft_strcmp(a, b) > 0)
			{
				lstswap_cmd(top, cur, cur->next);
				swapped = 1;
				break ;
			}
			cur = cur->next;
		}
	}
}

t_cmd	*browse_paths_wildcard(t_global *g, t_subcmd *subcmd, char *path)
{
	t_cmd	*new;
	char	*wildcard_word;
	char	*full_path;
	int		path_len;
	int		i;

	new = lstnew_nd_cmd(g, NULL);
	i = 0;
	path_len = lenpath_wildcard(subcmd);
	full_path = NULL;
	if (path_len > 0)
		full_path = file_full_path(g, &subcmd, &i, path_len);
	wildcard_word = get_wildcard_word(g, subcmd, i, path);
	new = check_match_wildcards(g, wildcard_word, full_path);
	lstsort_cmd(&new);
	if (new)
		join_subcmd_in_allcmd(new, get_rest_in_subcmd(g, subcmd, i));
	return (new);
}

void	handle_wildcard(t_global *g, t_cmds *cmds)
{
	t_cmd		*cmd;
	t_cmd		*new;
	t_subcmd	*subcmd;

	cmd = cmds->topcmd;
	while (cmd)
	{
		subcmd = cmd->subcmd;
		while (subcmd)
		{
			if (subcmd->wildcard)
			{
				new = browse_paths_wildcard(g, cmd->subcmd, NULL);
				lstreplace_nd_cmd(&cmds->topcmd, cmd, new);
				cmd = new;
				subcmd = cmd->subcmd;
				continue ;
			}
			subcmd = subcmd->next;
		}
		cmd = cmd->next;
	}
}
