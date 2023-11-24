/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:42:42 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/24 16:40:21 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

# ifndef BUFFER_SIZE
    # define BUFFER_SIZE 999
# endif

char    *get_next_line(int fd)
{ 
    int                 nbytes;
    static char         *buffer;
    char                temp[BUFFER_SIZE];
    static int          i;
    char                *line;

    line = NULL;
    if (fd < 0)
        return (NULL);
    while ((nbytes = read(fd, temp, BUFFER_SIZE)) > 0)
    {
        temp[nbytes] = '\0';
        if (buffer == NULL)
            buffer = ft_strdup(temp);
        else
            buffer = ft_strjoin(buffer, temp);
        if (ft_strchr(buffer + i, '\n') != NULL)
        {
            i = 0;
            line = ft_strdup(buffer);
            free(buffer);
            buffer = NULL;
            return (line);
        }
        i++;
    }
    // printf("%d\n", ft_strlen(buffer));
    if (nbytes == 0 && i > 0)
    {
        i = 0;
        line = ft_strdup(buffer);
        free(buffer);
        buffer = NULL;
        return (line);
    }
    return (NULL);
}


int main()
{
    int fd;

    fd = open("test.txt", O_RDWR | O_CREAT);
    printf("line -> %s\n", get_next_line(fd));
    printf("line -> %s\n", get_next_line(fd));
    printf("line -> %s\n", get_next_line(fd));
    // printf("line -> %s\n", get_next_line(fd));
    // printf("line -> %s\n", get_next_line(fd));
}