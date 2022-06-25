#include "get_next_line.h"

char	*get_res(unsigned int new_line_idx, char *buf)
{
	char			*res;
	unsigned int	i;

	res = (char *)malloc(new_line_idx);
	if (res == NULL)
		return (NULL);
	i = new_line_idx;
	while (i--)
		res[i] = buf[i];
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

char	*get_more_byte(char *buf, int fd, unsigned int *new_line_idx)
{
	char				*res;
	unsigned int		total_size;
	static unsigned int	count = 2;
	unsigned int		i;
	unsigned int		flag;

	total_size = BUFFER_SIZE * count;
	i = total_size - BUFFER_SIZE;
	flag = 1;
	res = (char *)malloc(total_size);
	if (res == NULL)
		return (NULL);
	while (i)
		res[i] = buf[i--];
	free (buf);
	read(fd, res[total_size - BUFFER_SIZE], BUFFER_SIZE);
	i = seek_new_line(res, &flag);
	if (flag)
	{
		*new_line_idx += i;
		return (get_res(*new_line_idx, res));
	}
	else
	{
		count++;
		*new_line_idx += BUFFER_SIZE;
		get_more_byte(res, fd, new_line_idx);
	}
}

char	*get_next_line(int fd)
{
	char				*buf;
	static unsigned int	new_line_idx = 0;
	unsigned int		flag;

	flag = 1;
	buf = (char*)malloc(BUFFER_SIZE);
	if (buf == 0)
		return (NULL);
	read(fd, buf, BUFFER_SIZE);
	new_line_idx += seek_new_line(buf, &flag);
	if (flag)
		return (get_res(new_line_idx, buf));
	else
		return (get_more_byte(buf, fd, &new_line_idx));
}