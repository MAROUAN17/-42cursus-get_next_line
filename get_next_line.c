/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:42:42 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/29 10:16:02 by maglagal         ###   ########.fr       */
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

char    *freeing_memory(char *ptr)
{
    free(ptr);
    ptr = NULL;
    return (NULL);
}

char    *make_line(char **buffer, char *line_rest, int *ptr_i)
{
    char        *line;
    
    *ptr_i = 0;
    line = ft_strdup(*buffer);
    if (!line) 
    {
        freeing_memory(line);
        return (freeing_memory(*buffer));
    }
    free(*buffer);
    if (line_rest && line_rest[0] != '\0')
    {    
        *buffer = ft_strdup(line_rest);
        if (!*buffer)
        {
            freeing_memory(line);    
            return (freeing_memory(*buffer));
        }
    }
    else
        *buffer = NULL;
    return (line);
}

void    terminating_string(char *buffer)
{
    int i;

    i = 0;
    while (buffer[i] != '\n')
        i++;
    buffer[i + 1] = '\0';
}

char    *get_next_line(int fd)
{ 
    int                 nbytes;
    static char         *buffer;
    char                temp[BUFFER_SIZE];
    char                *temp2;
    char                *line_rest;
    static int          i;

    line_rest = NULL;
    if (fd < 0)
        return (NULL);
    nbytes = read(fd, temp, BUFFER_SIZE);
    while (nbytes > 0 || (buffer && ft_strchr(buffer, '\n')))
    {
        temp[nbytes] = '\0';
        i += nbytes;
        if (buffer == NULL)
        {
            buffer = ft_strdup(temp);
            if (!buffer)
                return (freeing_memory(buffer));
        }
        else
        {
            temp2 = buffer;
            buffer = ft_strjoin(temp2, temp);
            if (!buffer)
                return (freeing_memory(temp2));
            freeing_memory(temp2);
        }
        line_rest = ft_strdup(ft_strchr(buffer, '\n'));
        if (line_rest != NULL)
        {
            line_rest++;
            terminating_string(buffer);
            return (make_line(&buffer, line_rest, &i));
        }
        nbytes = read(fd, temp, BUFFER_SIZE);
    }
    free(line_rest);
    line_rest = NULL;
    if (buffer && nbytes == 0)
        return (make_line(&buffer, line_rest, &i));
    return (NULL);
}


// int main()
// {
//     int fd;

//     fd = open("test.txt", O_RDWR | O_CREAT);
//     printf("line -> %s", get_next_line(fd));
//     printf("line -> %s", get_next_line(fd));
//     printf("line -> %s", get_next_line(fd));
//     printf("line -> %s", get_next_line(fd));
//     printf("line -> %s", get_next_line(fd));
//     printf("line -> %s", get_next_line(fd));
//     printf("line -> %s", get_next_line(fd));
//     printf("line -> %s", get_next_line(fd));
//     printf("line -> %s", get_next_line(fd));
//     printf("line -> %s", get_next_line(fd));
//     printf("line -> %s", get_next_line(fd));
// }