#include<stdlib.h>
#include<unistd.h>

char *realloc_line(char *s, int i, int n)
{
    char *str;

    if(!(str = malloc(n)))
        return(NULL);
    while(i-- > 0)
        str[i] = s[i];
    free(s);
    return(str);
}

char *gnl(int fd, int buf_size )
{
    int i = 0;
    char *line;

    if (!(line = malloc(buf_size)))
        return(NULL);
    while(read(fd, &(line[i]), 1))
    {
        if(line[i++] == '\n')
            break;
        if (i % buf_size == 0)
            if(!(line = realloc_line(line, i, i + buf_size)))
                return(NULL);
    }
    if (i == 0)
    {
        free(line);
        return(NULL);
    }
    if (!(line = realloc_line(line, i, i)))
        return(NULL);
    line[--i] = '\0';
    return(line);
}