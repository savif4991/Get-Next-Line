#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 256

char	*get_res(unsigned int new_line_idx, char *buf);
unsigned int	seek_new_line(char *buf, unsigned int *flag);
char	*get_more_byte(char *buf, int fd, unsigned int *new_line_idx);
char	*get_next_line(int fd);

#endif