/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:33:30 by rodeulio          #+#    #+#             */
/*   Updated: 2025/03/30 13:19:53 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *source)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(ft_strlen(source) + 1);
	if (!dst)
		return (NULL);
	while (source[i])
	{
		dst[i] = source[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
