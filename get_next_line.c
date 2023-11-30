/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:42:42 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/30 11:42:43 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

char    *make_line(char **buffer, char **next_buffer, int *ptr_i, char **reading_buffer)
{
    char        *line;
    
    *ptr_i = 0;
    line = ft_strdup(*buffer);
    if (!line)
    {
        freeing_memory(reading_buffer);
        freeing_memory(next_buffer);
        return (freeing_memory(buffer));
    }
    freeing_memory(buffer);
    if (*next_buffer && *next_buffer[0] != '\0')
    {
        *buffer = ft_strdup(*next_buffer);
        if (!*buffer)
        {
            freeing_memory(reading_buffer);
            return (freeing_memory(&line));
        }
    }
    freeing_memory(next_buffer);
    freeing_memory(reading_buffer);
    return (line);
}

char    *making_buffer(char **buffer, char **reading_buffer)
{
    char    *temp_buffer;
    
    if (*buffer == NULL)
    {
        *buffer = ft_strdup(*reading_buffer);
        if (!*buffer)
            freeing_memory(reading_buffer);
    }
    else
    {
        temp_buffer = *buffer;
        *buffer = ft_strjoin(temp_buffer, *reading_buffer);
        if (!*buffer)
            freeing_memory(reading_buffer);
        freeing_memory(&temp_buffer);
    }
    return (*buffer);
}

char    *check_newline(char **buffer, char **reading_buffer, char **line_rest)
{
    char    *check_nl;
    
    check_nl = ft_strchr(*buffer, '\n');
    if (check_nl != NULL)
    {
        check_nl++;
        if (*check_nl != '\0')
        {
            *line_rest = ft_strdup(check_nl);
            if (!*line_rest)
            {
                freeing_memory(reading_buffer);
                return (freeing_memory(buffer));
            }
        }
        *check_nl = '\0';
    }
    return (check_nl);
}

char    *get_next_line(int fd)
{ 
    int                 nbytes;
    static char         *buffer;
    char                *reading_buffer;
    char                *line_rest;
    char                *check_nl;
    static int          i;

    if (fd < 0)
        return (NULL);
    line_rest = NULL;
    reading_buffer = malloc(sizeof(char) * BUFFER_SIZE);
    if (!reading_buffer)
        return (freeing_memory(&buffer));
    nbytes = read(fd, reading_buffer, BUFFER_SIZE);
    while (nbytes > 0 || (buffer && ft_strchr(buffer, '\n')))
    {
        *(reading_buffer + nbytes) = '\0';
        i += nbytes;
        making_buffer(&buffer, &reading_buffer);
        check_nl = check_newline(&buffer, &reading_buffer, &line_rest);
        if (check_nl)
            return (make_line(&buffer, &line_rest, &i, &reading_buffer));
        nbytes = read(fd, reading_buffer, BUFFER_SIZE);
    }
    freeing_memory(&reading_buffer);
    if (buffer && nbytes == 0)
        return (make_line(&buffer, &line_rest, &i, &reading_buffer));
    return (NULL);
}


// int main()
// {
//     int fd;
//     clock_t start, end;
//     double cpu_time_used;

//     start = clock();

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
//     end = clock();
//     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
//     printf("\nExecution time: %f seconds\n", cpu_time_used);
// }