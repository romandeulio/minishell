/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:33:55 by rodeulio          #+#    #+#             */
/*   Updated: 2025/03/30 13:19:22 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	start;
	size_t	end;
	size_t	s_len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	s_len = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = s_len;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	dst = malloc(end - start + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, (s1 + start), (end - start + 1));
	return (dst);
}
