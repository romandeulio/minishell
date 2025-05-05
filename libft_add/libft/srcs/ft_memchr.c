/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:33:05 by rodeulio          #+#    #+#             */
/*   Updated: 2025/03/30 13:20:23 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	const char	*str;

	str = (const char *)s;
	if (size == 0)
		return (NULL);
	while (size > 0)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
		size--;
	}
	if ((char)c == '\0')
		return ((void *)str);
	return (NULL);
}
