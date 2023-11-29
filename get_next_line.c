/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:42:42 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/29 21:43:02 by maglagal         ###   ########.fr       */
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

char    *freeing_memory(char **ptr)
{
    free(*ptr);
    *ptr = NULL;
    return (NULL);
}

char    *make_line(char **buffer, char **next_buffer, int *ptr_i, char **temp)
{
    char        *line;
    
    *ptr_i = 0;
    line = ft_strdup(*buffer);
    if (!line)
    {
        freeing_memory(temp);
        freeing_memory(next_buffer);
        return (freeing_memory(buffer));
    }
    freeing_memory(buffer);
    if (*next_buffer && *next_buffer[0] != '\0')
    {
        *buffer = ft_strdup(*next_buffer);
        freeing_memory(next_buffer);
        if (!*buffer)
        {
            freeing_memory(buffer); //if buffer already has value allocated
            freeing_memory(temp);
            return (freeing_memory(&line));
        }
    }
    freeing_memory(next_buffer);
    freeing_memory(temp);
    return (line);
}

void    terminating_string(char *buffer)
{
    int     i;
    char    *position;

    i = 0;
    position = ft_strchr(buffer, '\n');
    position++;
    *position = '\0';
}

char    *get_next_line(int fd)
{ 
    int                 nbytes;
    static char         *buffer;
    char                *temp;
    char                *temp2;
    char                *line_rest;
    char                *check_nl;
    char                *n_buffer;
    static int          i;

    line_rest = NULL;
    n_buffer = NULL;
    temp = NULL;
    if (fd < 0)
        return (NULL);
    temp = malloc(sizeof(char) * BUFFER_SIZE);
    if (!temp)
        return (freeing_memory(&buffer));
    nbytes = read(fd, temp, BUFFER_SIZE);
    while (nbytes > 0 || (buffer && ft_strchr(buffer, '\n')))
    {
        *(temp + nbytes) = '\0';
        i += nbytes;
        if (buffer == NULL)
        {
            buffer = ft_strdup(temp);
            if (!buffer)
            {
                freeing_memory(&temp);
                return (freeing_memory(&buffer));
            }
        }
        else
        {
            temp2 = buffer;
            buffer = ft_strjoin(temp2, temp);
            if (!buffer)
            {
                freeing_memory(&temp);   
                return (freeing_memory(&buffer));
            }
            freeing_memory(&temp2);
        }
        if ((check_nl = ft_strchr(buffer, '\n')) != NULL)
        {
            check_nl++;
            if (*check_nl != '\0')
            {
                line_rest = ft_strdup(check_nl);
                if (!line_rest)
                {
                    freeing_memory(&temp);
                    return (freeing_memory(&buffer));
                }
            }
            terminating_string(buffer);
            return (make_line(&buffer, &line_rest, &i, &temp));
        }
        nbytes = read(fd, temp, BUFFER_SIZE);
    }
    freeing_memory(&temp);
    if (buffer && nbytes == 0)
        return (make_line(&buffer, &line_rest, &i, &temp));
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
//     printf("line -> %s", get_next_line(fd));
// }