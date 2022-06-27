#include "get_next_line.h"

/*
GNL Abstract
1. 처음 함수 호출했을 때
2. 두번째 이상 호출했을 때
(호출한 시점의 상태)
- rest_str에 그 전 호출에서 truncated된 문자열 존재, past_idx에 그 전 호출에서 찾은 개행문자 인덱스 존재 -
1-1 : BUFFER_SIZE 범위에 개행 존재 O
	idx 개행 문자 위치까지 증가
	get_res
2-2 : BUFFER_SIZE 범위에 개행 존재 X
	idx BUFFER_SIZE만큼 증가
	get_more_byte
*/

char	*get_res(unsigned int idx, unsigned int past_idx, char *buf, char *rest_str, unsigned int buf_call, unsigned int local_buf_call)
{
	char			*res;
	unsigned int	i;
	unsigned int	count;
	unsigned int	size;

	size = idx - past_idx;
	count = 0;
	i = 0;
	res = (char *)malloc(size);
	if (res == NULL)
		return (NULL);
	while (count < size)
	{
		if (count < buf_call * BUFFER_SIZE - past_idx)
			res[count] = rest_str[count++];
		else
			res[count++] = buf[i++];
	}
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

char	*malloc_more_byte(char *buf, unsigned int local_buf_call)
{
	unsigned int	i;
	char			*temp;

	i = 0;
	temp = (char *)malloc(BUFFER_SIZE * (local_buf_call + 1));
	if (temp == NULL)
		return (NULL);
	while (i < BUFFER_SIZE)
		temp[i] = buf[i++];
	free (buf);
	return (temp);
}

char	*get_next_line(int fd)
{
	char				*buf;
	char				*res;
	static unsigned int	idx = 0;
	static unsigned int	buf_call = 0;
	unsigned int		count;
	unsigned int		flag;
	unsigned int		past_idx;
	unsigned int		local_buf_call;
	static char			rest_str[BUFFER_SIZE] = {};

	flag = 1;
	buf = (char*)malloc(BUFFER_SIZE);
	if (buf == 0)
		return (NULL);
	past_idx = idx;
	local_buf_call = 0;
	while (1)
	{
		read(fd, buf + local_buf_call * BUFFER_SIZE, BUFFER_SIZE);
		local_buf_call++;
		idx += seek_new_line(buf, &flag);
		if (flag)
		{
			res = get_res(idx, past_idx, buf, rest_str, buf_call, local_buf_call);
			count = 0;
			while (BUFFER_SIZE * buf_call - (idx + count))
				rest_str[count] = buf[idx + count++];
			free (buf);
			buf_call += local_buf_call;
			return (res);
		}
		else
		{
			buf = malloc_more_byte(buf, local_buf_call);
			if (buf == NULL)
				return (NULL);
		}
	}
}