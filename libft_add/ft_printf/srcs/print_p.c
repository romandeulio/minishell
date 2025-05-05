/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:15:18 by rodeulio          #+#    #+#             */
/*   Updated: 2025/03/25 16:56:49 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	print_p(void *ptr)
{
	uintptr_t	address;
	int			len;

	if (!ptr)
		return (ft_putstr_fd("(nil)", 1), 5);
	address = (uintptr_t)ptr;
	len = 2;
	ft_putstr_fd("0x", 1);
	len += select_base_ul(address, 16);
	return (len);
}
