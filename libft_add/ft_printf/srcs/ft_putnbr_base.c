/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:03:33 by rodeulio          #+#    #+#             */
/*   Updated: 2025/03/25 16:55:22 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	select_base(int n, int base)
{
	if (base == 10)
		return (ft_putnbr_base(n, "0123456789"));
	else if (base == 16)
		return (ft_putnbr_base(n, "0123456789abcdef"));
	else if (base == 160)
		return (ft_putnbr_base(n, "0123456789ABCDEF"));
	else
		return (0);
}

int	ft_putnbr_base(int n, char *base)
{
	int	base_len;
	int	len;

	base_len = ft_strlen(base);
	len = 0;
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", 1);
		return (11);
	}
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n = -n;
		len++;
	}
	if (n >= base_len)
		len += ft_putnbr_base(n / base_len, base);
	ft_putchar_fd(base[n % base_len], 1);
	len++;
	return (len);
}
