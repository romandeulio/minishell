/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:49:32 by rodeulio          #+#    #+#             */
/*   Updated: 2025/04/04 15:39:46 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdint.h>

int	ft_printf(const char *str, ...);
int	select_print(const char c, va_list *ap);
int	select_base(int n, int base);
int	select_base_u(unsigned int n, int base);
int	select_base_ul(unsigned long n, int base);
int	ft_putnbr_base(int n, char *base);
int	ft_putnbr_base_u(unsigned int n, char *base);
int	ft_putnbr_base_ul(unsigned long n, char *base);
int	print_c(char c);
int	print_s(char *str);
int	print_p(void *ptr);

#endif
