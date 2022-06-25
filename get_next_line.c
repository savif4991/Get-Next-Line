#include "get_next_line.h"

char	*get_res(unsigned int new_line_idx, unsigned int past_new_line_idx, char *buf)
{
	char			*res;
	unsigned int	i;
	unsigned int	count;

	count = 0;
	i = new_line_idx - past_new_line_idx;
	res = (char *)malloc(i);
	if (res == NULL)
		return (NULL);
	while (past_new_line_idx < new_line_idx)
		res[count++] = buf[past_new_line_idx++];
	free (buf);
	return (res);
}

unsigned int	seek_new_line(char *buf, unsigned int *flag)
{
	unsigned int	i;

	i = 0;
	while (buf[i] != '\n')
	{
		i++;
		if (!buf[i])
		{
			*flag = 0;
			return (i);
		}
	}
	return (i);
}

char	*get_more_byte(char *buf, int fd, unsigned int past_new_line_idx, unsigned int *new_line_idx)
{
	char				*res;
	unsigned int		total_size;
	static unsigned int	count = 2;
	unsigned int		i;
	unsigned int		flag;

	total_size = BUFFER_SIZE * count - past_new_line_idx;
	i = total_size - BUFFER_SIZE - past_new_line_idx;
	flag = 1;
	res = (char *)malloc(total_size);
	if (res == NULL)
		return (NULL);
	while (i)
		res[i] = buf[i--];
	free (buf);
	read(fd, &res[total_size - BUFFER_SIZE], BUFFER_SIZE);
	i = seek_new_line(res, &flag);
	if (flag)
	{
		*new_line_idx += i;
		return (get_res(*new_line_idx, past_new_line_idx, res));
	}
	else
	{
		count++;
		*new_line_idx += BUFFER_SIZE;
		get_more_byte(res, fd, past_new_line_idx, new_line_idx);
	}
}
//한 차례 GNL이 실행 된 후 가져간 개행문자까지는 좋음.
//뒤의 나머지 문자열의 보존은? -> static char	*rest_str[];
char	*get_next_line(int fd)
{
	char				*buf;
	static unsigned int	new_line_idx = 0;
	unsigned int		flag;
	unsigned int		past_new_line_idx;
	static char			rest_str[BUFFER_SIZE]; //잘리고 난 나머지 저장..필요

	flag = 1;
	buf = (char*)malloc(BUFFER_SIZE);
	if (buf == 0)
		return (NULL);
	past_new_line_idx = new_line_idx;
	read(fd, buf, BUFFER_SIZE);
	new_line_idx += seek_new_line(buf, &flag);
	if (flag)
		return (get_res(new_line_idx, past_new_line_idx, buf));
	else
		return (get_more_byte(buf, fd, past_new_line_idx, &new_line_idx));
}