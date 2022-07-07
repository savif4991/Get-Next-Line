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
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

static void	*ft_memset(void *s, int c, size_t n)
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

static char	*append_res(char *res_str, char *buf)
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

static unsigned int	seek_new_line(char *buf)
{
	unsigned int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i] != '\n')
	{
		i++;
		if (!buf[i])
			return (0);
	}
	return (i);
}

static char	*get_ret(char *buf, t_list **s_list)
{
	char			*ret;
	char			*temp;
	unsigned int	nl_idx;
	t_list			*adr;

	adr = *s_list;
	nl_idx = seek_new_line(adr->content);
	free (buf);
	if (nl_idx)
	{
		ret = (char *)malloc(nl_idx + 2);
		if (!ret)
			return (ft_lstclear(s_list));
		ft_strlcpy(ret, adr->content, nl_idx + 2);
		temp = (char *)malloc(ft_strlen(adr->content) - nl_idx);
		ft_strlcpy(temp, adr->content + nl_idx + 1,
			ft_strlen(adr->content) - nl_idx);
		free (adr->content);
		adr->content = temp;
		return (ret);
	}
	else
		return (adr->content);
}

char	*get_next_line(int fd)
{
	char			*buf;
	static t_list	*s_list = NULL;

	buf = (char *)malloc(BUFFER_SIZE);
	if (!buf || fd < 0 || !read(fd, buf, BUFFER_SIZE) || !buf[0])
	{
		if (buf)
			free (buf);
		return (ft_lstclear(&s_list));
	}
	if (!s_list)
		s_list = ft_lstnew(NULL);
	while (1)
	{
		s_list->content = append_res(s_list->content, buf);
		if (!s_list->content)
			return (ft_lstclear(&s_list));
		ft_memset(buf, 0, BUFFER_SIZE);
		if (seek_new_line(s_list->content) || !read(fd, buf, BUFFER_SIZE))
			return (get_ret(buf, &s_list));
	}
}
