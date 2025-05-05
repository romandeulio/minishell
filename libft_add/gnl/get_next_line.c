/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:33:36 by rodeulio          #+#    #+#             */
/*   Updated: 2025/04/10 16:08:07 by rodeulio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remain[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1023)
		return (NULL);
	remain[fd] = add_to_remain(fd, remain[fd]);
	if (!remain[fd] || remain[fd][0] == '\0')
	{
		free(remain[fd]);
		remain[fd] = NULL;
		return (NULL);
	}
	line = extract_line(remain[fd]);
	remain[fd] = clean_remain(remain[fd]);
	return (line);
}

char	*add_to_remain(int fd, char *remain)
{
	char	*buffer;

	if (!remain)
	{
		remain = ft_calloc(1, sizeof(char));
		if (!remain)
			return (NULL);
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	remain = read_to_buffer(fd, buffer, remain);
	free(buffer);
	return (remain);
}

char	*read_to_buffer(int fd, char *buffer, char *remain)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (!ft_strchr(remain, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(remain), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(remain, buffer);
		free(remain);
		if (!temp)
			return (NULL);
		remain = temp;
	}
	return (remain);
}

char	*extract_line(char *remain)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	if (!remain || remain[0] == '\0')
		return (NULL);
	while (remain[len] && remain[len] != '\n')
		len++;
	if (remain[len] == '\n')
		len++;
	line = malloc((len + 1));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = remain[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*clean_remain(char *remain)
{
	int		i;
	int		j;
	char	*new_remain;

	i = 0;
	j = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (remain[i] == '\n')
		i++;
	if (!remain[i])
		return (free(remain), NULL);
	new_remain = malloc(ft_strlen(remain + i) + 1);
	if (!new_remain)
		return (free(remain), NULL);
	while (remain[i])
		new_remain[j++] = remain[i++];
	new_remain[j] = '\0';
	free(remain);
	return (new_remain);
}
