#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int             main(int argc, char **argv)
{

        char    *line;
        int             fd1, fd2, i;
        int test;

        (void)argc;
        (void)argv;
        line = NULL;
        i = 0;
        fd1 = open("test", O_RDONLY);
        //fd2 = open("test2", O_RDONLY);
	while (i < 40 && (test = get_next_line(fd1, &line)))
	{
		printf("%s\n", line);
		i++;
	}
	printf("  %d", test);
	free(line);
	close(fd1);
    //     while (i < 8 && get_next_line(fd1, &line))
	// {
	// 	printf("%s\n", line);
	// 	i++;
	// }
    //     while (i < 12 && get_next_line(fd2, &line))
	// {
	// 	printf("%s\n", line);
	// 	i++;
	// }
    //     while (i < 16 && get_next_line(fd1, &line))
	// {
	// 	printf("%s\n", line);
	// 	i++;
	// }
//        test = get_next_line(fd1, &line);
//        printf("%s\n", line);
//        test = get_next_line(fd1, &line);
//          printf("%s\n", line);
        // test = get_next_line(fd1, &line);
        // printf("%s\n", line);
        return (0);
}
