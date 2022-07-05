#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
int main()
{
	int i = 0;
	int fd = open("./test", O_RDONLY);
	printf("%s\n", get_next_line(0));
	printf("%s\n", get_next_line(0));
	printf("%s\n", get_next_line(0));
	printf("%s\n", get_next_line(0));
	return (0);
}