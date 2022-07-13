#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>
int main()
{
	int fd0 = open("./41_with_nl", O_RDONLY);
	int fd1 = open("./42_with_nl", O_RDONLY);
	int fd2 = open("./43_with_nl", O_RDONLY);
	printf("%s", get_next_line(1000));
	printf("%s", get_next_line(fd0));
	printf("%s", get_next_line(1001));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(1002));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(1003));
	printf("%s", get_next_line(fd0));
	printf("%s", get_next_line(1004));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(1005));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd0));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd2));
	return (0);
}