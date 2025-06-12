/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_subfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:17:46 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/06/12 00:24:02 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"

// t_subfile	*lstcpy_subtoks_subfile(t_global *g, t_subtok *subtok)
// {
// 	t_subfile	*last;
// 	t_subfile	*new;
// 	int			size;

// 	new = NULL;
// 	while (subtok)
// 	{
// 		size = ft_strlen(subtok->subword);
// 		lstadd_back_subfile(&new, lstnew_nd_subfile(g, size));
// 		last = lstget_last_nd_subfile(new);
// 		ft_strcpy(last->subname, subtok->subword);
// 		last->state = subtok->state;
// 		last->varenv = subtok->varenv;
// 		last->wildcard = subtok->wildcard;
// 		subtok = subtok->next;
// 	}
// 	return (new);
// }

// t_subfile	*lstnew_nd_subfile(t_global *g, int size)
// {
// 	t_subfile	*new;

// 	new = malloc(sizeof(t_subfile));
// 	if (!new)
// 		exit_free(g, "Malloc", -1, 1);
// 	new->subname = malloc(sizeof(char) * (size + 1));
// 	if (!new->subname)
// 		exit_free(g, "Malloc", -1, 1);
// 	new->subname[0] = '\0';
// 	new->state = NORMAL;
// 	new->varenv = 0;
// 	new->wildcard = 0;
// 	new->next = NULL;
// 	return (new);
// }

// void	lstfree_subfile(t_subfile **subfile)
// {
// 	t_subfile	*tmp;
// 	t_subfile	*cur;

// 	tmp = *subfile;
// 	cur = *subfile;
// 	while (cur)
// 	{
// 		cur = cur->next;
// 		free(tmp->subname);
// 		free(tmp);
// 		tmp = cur;
// 	}
// 	*subfile = NULL;
// }

// void	lstadd_back_subfile(t_subfile **top, t_subfile *nd)
// {
// 	t_subfile	*tmp;

// 	if (!*top)
// 	{
// 		*top = nd;
// 		return ;
// 	}
// 	tmp = *top;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = nd;
// }

// void	lstdelete_subfile(t_subfile **top, t_subfile *dlt)
// {
// 	t_subfile	*cur;
// 	t_subfile	*prev;

// 	if (!top || !*top || !dlt)
// 		return ;
// 	cur = *top;
// 	prev = NULL;
// 	while (cur)
// 	{
// 		if (cur == dlt)
// 		{
// 			if (!prev)
// 				*top = cur->next;
// 			else
// 				prev->next = cur->next;
// 			free(cur->subname);
// 			free(cur);
// 			break ;
// 		}
// 		prev = cur;
// 		cur = cur->next;
// 	}
// }

// t_subfile	*lstget_last_nd_subfile(t_subfile *top)
// {
// 	t_subfile	*tmp;

// 	if (!top)
// 		return (NULL);
// 	tmp = top;
// 	while (tmp && tmp->next)
// 		tmp = tmp->next;
// 	return (tmp);
// }
