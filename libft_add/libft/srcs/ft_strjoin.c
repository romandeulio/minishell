/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:33:38 by rodeulio          #+#    #+#             */
/*   Updated: 2025/05/26 23:36:19 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = malloc(s1_len + s2_len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		dst[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		dst[j++] = s2[i++];
	dst[j] = '\0';
	return (dst);
}
