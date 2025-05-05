/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:33:34 by rodeulio          #+#    #+#             */
/*   Updated: 2025/04/11 19:40:58 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "get_next_line.h"

static size_t	ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

static char	*ft_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

static char	*ft_strjoin(char *s1, char *s2)
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
	while (s1[i])
		dst[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dst[j++] = s2[i++];
	dst[j] = '\0';
	return (dst);
}

static void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	if (count && size > (size_t)-1 / count)
		return (NULL);
	tab = malloc(count * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, (count * size));
	return (tab);
}

static void	ft_bzero(void *s, size_t n)
{
	if (n > 0)
	{
		while (n > 0)
		{
			*(unsigned char *)s = 0;
			n--;
			s++;
		}
	}
}*/
