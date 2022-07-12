#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
int main()
{
	int fd1 = open("./test1", O_RDONLY);
	int fd2 = open("./test2", O_RDONLY);
	int fd3 = open("./test3", O_RDONLY);
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd2));
	return (0);
}