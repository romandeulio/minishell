/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:32:58 by rodeulio          #+#    #+#             */
/*   Updated: 2025/03/30 13:20:30 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dst;
	t_list	*temp;

	dst = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!lst)
		{
			ft_lstclear(&dst, del);
			return (NULL);
		}
		ft_lstadd_back(&dst, temp);
		lst = lst->next;
	}
	return (dst);
}
