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
#include "get_next_line_bonus.h"

static unsigned int	seek_new_line(char *buf)
{
	unsigned int	i;

	i = 0;
	while (buf[i] != '\n')
	{
		i++;
		if (!buf[i])
			return (0);
	}
	return (i);
}
//OS에 따라 EOF값이 다른가?
static char	*get_ret_no_nl(char *res_str)
{
	int	i;

	i = 0;
	while (ft_isascii(res_str[i]))
		i++;
	res_str[i] = '\0';
	return (res_str);
}

static char	*get_ret_nl(char *res_str)
{
	char			*ret;
	unsigned int	nl_idx;

	nl_idx = seek_new_line(res_str);
	ret = (char *)malloc(nl_idx + 2);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, res_str, nl_idx + 2);
	return (ret);
}

static char	*renew_res(char *res_str)
{
	unsigned int	nl_idx;
	char			*ret;

	nl_idx = seek_new_line(res_str);
	ret = (char *)malloc(ft_strlen(res_str) - nl_idx);
	ft_strlcpy(ret, res_str + nl_idx + 1, ft_strlen(res_str) - nl_idx);
	free (res_str);
	return (ret);
}

char	*get_next_line(int fd)
{
	char			*buf;
	char			*ret;
	static char		*res_str[256]; //static char* 변수이므로, 함수가 다시 호출될 때 값을 그대로 가지고 있음.

	buf = (char *)malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	while (1)
	{
		ft_memset(buf, 0, BUFFER_SIZE);
		if (!read(fd, buf, BUFFER_SIZE))
			return (NULL);
		res_str[fd] = append_res(res_str[fd], buf); //res_str의 끝에 이어 붙임
		if (seek_new_line(res_str[fd])) //res_str에 개행이 존재
		{
			ret = get_ret_nl(res_str[fd]);
			res_str[fd] = renew_res(res_str[fd]);
			return (ret);
		}
		else if (ft_strlen(buf) != BUFFER_SIZE)
			return (res_str[fd]);
	}
}
