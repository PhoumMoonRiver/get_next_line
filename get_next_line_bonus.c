/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njerasea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:59:11 by njerasea          #+#    #+#             */
/*   Updated: 2022/08/19 16:01:17 by njerasea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_next(char *buffer, size_t lenline)
{
	char	*line;

	if (!buffer[lenline])
	{
		free(buffer);
		return (NULL);
	}
	if (buffer[lenline] == '\n')
		lenline += 1;
	line = ft_substr(buffer, lenline, ft_strlen_end(&buffer[lenline], '\0'));
	free(buffer);
	return (line);
}

char	*ft_line(char *buffer, size_t lenline)
{
	char	*line;
	
	if (!buffer[0])
		return (NULL);
	if (buffer[lenline] == '\n')
		lenline += 1;
	line = ft_substr(buffer, 0, lenline);
	return (line);
}

char	*ft_readtojoin(int fd, char *buffer)
{
	char		*res;
	int		numread;

	if (!buffer)
	{
		buffer = malloc(1);
		buffer[0] = '\0';
	}
	res = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!res)
		return (NULL);
	numread = 1;
	while (numread > 0)
	{
		numread = read(fd, res, BUFFER_SIZE);
		if (numread < 0)
		{
			free(res);
			return (NULL);
		}
		res[numread] = '\0';
		buffer = ft_strjoin(buffer, res);
		if (ft_strrchr(res, '\n'))
			break ;
	}
	free(res);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;
	size_t		lenline;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = ft_readtojoin(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	lenline = ft_strlen_end(buffer[fd], '\n');
	line = ft_line(buffer[fd], lenline);
	buffer[fd] = ft_next(buffer[fd], lenline);
	return (line);
}
