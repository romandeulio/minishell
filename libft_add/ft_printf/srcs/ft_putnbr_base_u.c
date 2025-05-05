/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:01:05 by rodeulio          #+#    #+#             */
/*   Updated: 2025/03/25 16:57:15 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	select_base_u(unsigned int n, int base)
{
	if (base == 10)
		return (ft_putnbr_base_u(n, "0123456789"));
	else if (base == 16)
		return (ft_putnbr_base_u(n, "0123456789abcdef"));
	else if (base == 160)
		return (ft_putnbr_base_u(n, "0123456789ABCDEF"));
	else
		return (0);
}

int	ft_putnbr_base_u(unsigned int n, char *base)
{
	unsigned int	base_len;
	int				len;

	base_len = ft_strlen(base);
	len = 0;
	if (n >= base_len)
		len += ft_putnbr_base_u(n / base_len, base);
	ft_putchar_fd(base[n % base_len], 1);
	len++;
	return (len);
}

int	select_base_ul(unsigned long n, int base)
{
	if (base == 10)
		return (ft_putnbr_base_ul(n, "0123456789"));
	else if (base == 16)
		return (ft_putnbr_base_ul(n, "0123456789abcdef"));
	else if (base == 160)
		return (ft_putnbr_base_ul(n, "0123456789ABCDEF"));
	else
		return (0);
}

int	ft_putnbr_base_ul(unsigned long n, char *base)
{
	unsigned long	base_len;
	int				len;

	base_len = ft_strlen(base);
	len = 0;
	if (n >= base_len)
		len += ft_putnbr_base_ul(n / base_len, base);
	ft_putchar_fd(base[n % base_len], 1);
	len++;
	return (len);
}
