/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:32:36 by rodeulio          #+#    #+#             */
/*   Updated: 2025/03/30 13:20:49 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	dst_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*dst;
	int		size;
	long	num;

	size = dst_size(n);
	num = n;
	dst = malloc(size + 1);
	if (!dst)
		return (NULL);
	dst[size] = '\0';
	if (num < 0)
	{
		num = -num;
		dst[0] = '-';
	}
	if (num == 0)
		dst[0] = '0';
	while (num > 0)
	{
		dst[--size] = (num % 10) + '0';
		num /= 10;
	}
	return (dst);
}
