// open prereq.
#include <fcntl.h>

#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int fd;
    char *line;
    int i;

    fd = open("test_files/41_with_nl.txt", O_RDONLY);
    line = get_next_line(fd);
    i = 0;
    // printf("-main start\n");
    while (line)
    {
        // printf("#%i: |%s|", i, line);
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
        // printf("%s", line);
        i++;
    }
    // static char stat_arr[100];
    // int bytes_read;
    // int fd;
    // fd = open("test_files/41_with_nl.txt", O_RDONLY);
    
    // bytes_read = read(fd, stat_arr, 100);
    // printf("bytes_read: %i\n", bytes_read);
    // printf("read: %s", stat_arr); 
    // printf("\n-main finished\n");
}