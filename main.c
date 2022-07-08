#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
int main()
{
	int fd1 = open("./test1", O_RDONLY);
	int fd2 = open("./test2", O_RDONLY);
	int fd3 = open("./test3", O_RDONLY);
	//close(fd);
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	printf("%s\n", get_next_line(fd1));
	printf("%s\n", get_next_line(fd2));
	printf("%s\n", get_next_line(fd3));
	return (0);
}