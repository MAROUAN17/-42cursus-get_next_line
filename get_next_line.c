#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

# ifndef BUFFER_SIZE
    # define BUFFER_SIZE 999
# endif



char    *make_line(int start, int end, char *buffer)
{
    char        *line;
    int         j;

    j = 0;
    line = malloc((end - start) + 1);
    if (!line)
        return (NULL);
    while((j + start) < end)
    {
        line[j] = buffer[j + start];
        j++;
    }
    line[j] = '\0';
    return (line);
}

char    *get_next_line(int fd)
{ 
    int             nbytes;
    char            c;
    static char     buffer[BUFFER_SIZE];
    char            temp[BUFFER_SIZE];
    static int      i;
    static int      start;
    static int      end;
    char            *line;

    start = i;  
    while ((nbytes = read(fd, temp, BUFFER_SIZE)) > 0)
    {
        printf("i -> %d\n", i);
        if (!nbytes)
            return (NULL);
        if (temp[0] == '\n' || temp[0] == '\0')
        {
            i++;
            return (line);
        }
        line = ft_strjoin(buffer, temp);
        i++;
    }
    // while (i < BUFFER_SIZE && buffer[i] != '\n' && buffer[i] != '\0')
    //     i++;
    // end = i;
    // if (i <= ft_strlen(buffer) && (buffer[i] == '\n' || buffer[i] == '\0')) 
    // {
    //     line = make_line(start, end, buffer);
    //     start = ++i;
    //     return (line);
    // }
    return (NULL);
}

int main()
{
    int fd;

    fd = open("test.txt", O_RDWR | O_CREAT);
    printf("line -> %s\n", get_next_line(fd));
    printf("line -> %s\n", get_next_line(fd));
}