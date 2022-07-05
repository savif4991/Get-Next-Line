/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:04:51 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/28 15:04:52 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while ((i + 1 < size) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (size != 0)
		dst[i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i);
}

unsigned int	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (i < n)
	{
		p[i] = (char)c;
		i++;
	}
	return (s);
}

char	*append_res(char *res_str, char *buf)
{
	char	*ret;

	if (!res_str)
	{
		ret = (char *)malloc(BUFFER_SIZE + 1);
		if (!ret)
			return (NULL);
		ft_strlcpy(ret, buf, BUFFER_SIZE + 1);
	}
	else
	{
		ret = (char *)malloc(ft_strlen(res_str) + BUFFER_SIZE + 1);
		if (!ret)
			return (NULL);
		ft_strlcpy(ret, res_str, ft_strlen(res_str) + 1);
		ft_strlcpy(ret + ft_strlen(res_str), buf, BUFFER_SIZE + 1);
		free (res_str);
	}
	return (ret);
}

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
