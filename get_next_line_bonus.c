/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:44:23 by maglagal          #+#    #+#             */
/*   Updated: 2023/12/04 11:42:39 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*freeing_memory(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*make_line(char **buffer, char **next_buffer, char **r_buffer)
{
	char	*line;

	line = ft_strdup(*buffer);
	if (!line)
	{
		freeing_memory(r_buffer);
		freeing_memory(next_buffer);
		return (freeing_memory(buffer));
	}
	freeing_memory(buffer);
	if (*next_buffer && *next_buffer[0] != '\0')
	{
		*buffer = ft_strdup(*next_buffer);
		if (!*buffer)
		{
			freeing_memory(next_buffer);
			freeing_memory(r_buffer);
			return (freeing_memory(&line));
		}
		freeing_memory(next_buffer);
	}
	freeing_memory(r_buffer);
	return (line);
}

static char	*making_buffer(char **buffer, char **r_buffer, int nbytes)
{
	char	*temp_buffer;

	*(*r_buffer + nbytes) = '\0';
	if (*buffer == NULL)
	{
		*buffer = ft_strdup(*r_buffer);
		if (!*buffer)
			return (freeing_memory(r_buffer));
	}
	else
	{
		temp_buffer = *buffer;
		*buffer = ft_strjoin(temp_buffer, *r_buffer);
		if (!*buffer)
		{
			freeing_memory(&temp_buffer);
			return (freeing_memory(r_buffer));
		}
		freeing_memory(&temp_buffer);
	}
	return (*buffer);
}

static char	*check_newline(char **buffer, char **r_buffer, char **line_rest)
{
	char	*check_nl;

	check_nl = ft_strchr(*buffer, '\n');
	if (check_nl != NULL)
	{
		check_nl++;
		if (*check_nl != '\0')
		{
			*line_rest = ft_strdup(check_nl);
			if (!*line_rest)
			{
				freeing_memory(r_buffer);
				return (freeing_memory(buffer));
			}
		}
		terminating_string(*buffer);
	}
	return (check_nl);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	int			nbytes;
	char		*r_buffer;
	char		*line_rest;

	line_rest = NULL;
	r_buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (fd < 0 || fd > OPEN_MAX || !r_buffer || read(fd, "", 0) < 0)
	{
		if (fd > 0)
			freeing_memory(&buffer[fd]);
		return (freeing_memory(&r_buffer));
	}
	nbytes = read(fd, r_buffer, BUFFER_SIZE);
	while (nbytes > 0 || (buffer[fd] && ft_strchr(buffer[fd], '\n')))
	{
		making_buffer(&buffer[fd], &r_buffer, nbytes);
		if (buffer[fd] && check_newline(&buffer[fd], &r_buffer, &line_rest))
			return (make_line(&buffer[fd], &line_rest, &r_buffer));
		nbytes = read(fd, r_buffer, BUFFER_SIZE);
	}
	freeing_memory(&r_buffer);
	if (buffer[fd] && nbytes == 0)
		return (make_line(&buffer[fd], &line_rest, &r_buffer));
	return (freeing_memory(&buffer[fd]));
}
