#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int ac, char **av)
{
   
    int     fd;
    int     nb_line;
    char    *line;
    int     i;
    
    printf("-----BUFFER_SIZE: %d-----\n", BUFFER_SIZE);
    if (ac == 1)
    {
        nb_line = 1;
        fd = STDIN_FILENO;
        printf("-fd is %d-\n", fd);
        printf("Enter input here (CTRL+D to end input): \n");
        line = get_next_line(fd);
        if (!line)
            printf("ERROR: line %d -> %s\n", nb_line++, line);
	    while (line)
	    {
	    	printf("line %d -> %s", nb_line++, line);
            free(line);
	    	line = get_next_line(fd);
	    }
    }
    else
    {
        i = 1;
        while (i < ac)
        {
            printf("-----running %s-----\n", av[i]);
            nb_line = 1;
            fd = open(av[i], O_RDONLY);
            printf("-fd is %d-\n", fd);
	        line = get_next_line(fd);
	        if (!line)
	        	printf("ERROR: line %d -> %s\n", nb_line++, line);
	        while (line)
	        {
	        	printf("line %d -> %s", nb_line++, line);
                free(line);
	        	line = get_next_line(fd);
	        }
	        printf("-Now reach the end of the file-\n");
            printf("-Call get_next_line function one more times-\n");
            if (line)
                free(line);
	        line = get_next_line(fd);
	        printf("line %d -> %s\n", nb_line++, line);
            i++;
        }
    }
    
    printf("-----TEST END-----\n");
    if (line)
        free(line);
    return (0);
}
