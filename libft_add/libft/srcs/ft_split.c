/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:33:26 by rodeulio          #+#    #+#             */
/*   Updated: 2025/06/04 18:54:40 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_strndup(char *src, int len)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	word_len;
	char	**dst;

	word_len = 0;
	dst = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (c == *s && word_len > 0)
		{
			dst[i++] = ft_strndup((char *)s - word_len, word_len);
			word_len = 0;
		}
		else if (c != *s)
			word_len++;
		s++;
	}
	if (word_len > 0)
		dst[i++] = ft_strndup((char *)s - word_len, word_len);
	dst[i] = NULL;
	return (dst);
}
