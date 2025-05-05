/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:22:49 by rodeulio          #+#    #+#             */
/*   Updated: 2025/03/26 23:23:16 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	select_print(const char c, va_list *ap)
{
	if (c == 'c')
		return (print_c(va_arg(*ap, int)));
	else if (c == 's')
		return (print_s(va_arg(*ap, char *)));
	else if (c == 'p')
		return (print_p(va_arg(*ap, void *)));
	else if (c == 'd' || c == 'i')
		return (select_base(va_arg(*ap, int), 10));
	else if (c == 'u')
		return (select_base_u(va_arg(*ap, unsigned int), 10));
	else if (c == 'x')
		return (select_base_u(va_arg(*ap, unsigned int), 16));
	else if (c == 'X')
		return (select_base_u(va_arg(*ap, unsigned int), 160));
	else if (c == '%')
		return (ft_putchar_fd('%', 1), 1);
	else
		return (print_c(c));
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	ap;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
			len += select_print(str[++i], &ap);
		else
		{
			ft_putchar_fd(str[i], 1);
			len++;
		}
		i++;
	}
	va_end(ap);
	return (len);
}
