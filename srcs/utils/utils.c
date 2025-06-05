/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbrecqueville <nicolasbrecquevill    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:49:40 by nicolasbrec       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/04 19:08:36 by nicolasbrec      ###   ########.fr       */
=======
/*   Updated: 2025/06/03 21:39:00 by rodeulio         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_num_str(char *str)
{
	if (!str || *str == '\0')
        return (0);
    if (*str == '-' || *str == '+')
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

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

void	free_tabstr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

<<<<<<< HEAD
=======
int tab_size (char **array)
{
    int i;

    i = 0;
    if (!array)
        return (0);
    while (array[i])
        i++;
    return (i);
}

>>>>>>> main
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

<<<<<<< HEAD
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
=======
	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
>>>>>>> main
}
