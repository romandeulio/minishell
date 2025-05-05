/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:33:39 by rodeulio          #+#    #+#             */
/*   Updated: 2025/04/12 22:46:30 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// get_next_line.c
char	*get_next_line(int fd);
char	*extract_line(char *remain);
char	*add_to_remain(int fd, char *remain);
char	*read_to_buffer(int fd, char *buffer, char *remain);
char	*clean_remain(char *remain);

#endif
