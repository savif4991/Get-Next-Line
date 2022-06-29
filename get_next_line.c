/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:04:31 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/28 15:04:32 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*get_ret(char *res_str, char *rest_str)
{
	unsigned int	i;
	unsigned int	res_str_len;
	unsigned int	count;
	char			*ret;

	res_str_len = ft_strlen(res_str);
	i = seek_new_line(res_str);
	ret = (char*)malloc(i);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, res_str, i);
	count = 0;
	while (i++ < res_str_len)
		rest_str[count++] = res_str[i];
	rest_str[count] = '\n';
	return (ret);
}

unsigned int	seek_new_line(char *buf)
{
	unsigned int	i;

	i = 0;
	while (buf[i] != '\n')
	{
		i++;
		if (!buf[i])
			return (i);
	}
	return (i);
}

char	*strjoin_free(char const *s1, char const *s2)
{
	int				i;
	unsigned int	s1_len;
	char			*res;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 1));
	if (res == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		res[s1_len + i] = s2[i];
		i++;
	}
	res[s1_len + i] = '\0';
	//free(s2);
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int		i;
	unsigned char		j;

	i = 0;
	j = (unsigned char)c;
	if (j != '\0')
	{
		while (s[i])
		{
			if (s[i] == j)
				return ((char *)&s[i]);
			else
				i++;
		}
	}
	else
	{
		while (s[i])
			i++;
		return ((char *)&s[i]);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*res_str;
	static char	*rest_str[BUFFER_SIZE] = {};

	buf = (char*)malloc(BUFFER_SIZE);
	if (buf == 0)
		return (NULL);
	res_str = buf;
	while (1)
	{
		read(fd, buf, BUFFER_SIZE);
		res_str = strjoin_free(res_str, buf);
		if (!res_str)
			return (NULL);
		if (ft_strchr(res_str, '\n'))
		{
			free (buf);
			res_str = get_ret(res_str, rest_str);
			return (res_str);
		}
	}
}
