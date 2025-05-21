/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:49:40 by nicolasbrec       #+#    #+#             */
/*   Updated: 2025/05/21 12:45:49 by nicolasbrec      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_strndup(const char *s, int size)
{
	char	*new;
	int		i;

    if (size < 0)
        size = 0;
	if (!s)
		return (NULL);
    new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && i < size && size > 0)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
