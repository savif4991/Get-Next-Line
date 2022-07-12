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

char	*concat(char *str, char *buf)
{
	char	*temp;

	if (!str)
	{
		temp = (char *)malloc(BUFFER_SIZE);
		if (!temp)
			return (NULL);
		ft_memcpy(temp, buf, BUFFER_SIZE);
	}
	else
	{
		temp = (char *)malloc(ft_strlen(str) + BUFFER_SIZE);
		if (!temp)
			return (NULL);
		ft_memcpy(temp, str, ft_strlen(str));
		ft_memcpy(temp + ft_strlen(str), buf, BUFFER_SIZE);
		free (str);
	}
	return (temp);
}

static int	seek_nl(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (-1);
	while (buf[i] != '\n')
	{
		i++;
		if (!buf[i])
			return (-1);
	}
	return (i);
}

char	*get_ret_nl(t_list **p, char *buf)
{
	char	*ret;
	t_list	*adr;
	int		nl_idx;
	char	*temp;

	adr = *p;
	nl_idx = seek_nl(adr->str);
	free (buf);
	ret = (char *)malloc(nl_idx + 2);
	temp = (char *)malloc(ft_strlen(adr->str) - nl_idx);
	if (!ret || !temp)
		return (ft_lstdel(p, buf));
	ft_memcpy(ret, adr->str, nl_idx + 1);
	ret[nl_idx + 2] = '\0';
	ft_memcpy(temp, adr->str + nl_idx + 1, ft_strlen(adr->str) - nl_idx);
	free (adr->str);
	adr->str = temp;
	if (adr->last_ret)
		free (adr->last_ret);
	adr->last_ret = ret;
	return (ret);
}

char	*get_ret_nonl(t_list **p, char *buf)
{
	char	*ret;
	t_list	*adr;

	free (buf);
	adr = *p;
	ret = (char *)malloc(ft_strlen(adr->str));
	if (!ret)
		return (ft_lstdel(p, buf));
	ft_memcpy(ret, adr->str, ft_strlen(adr->str));
	adr->str[0] = '\0';
	if (adr->last_ret)
		free (adr->last_ret);
	adr->last_ret = ret;
	return (ret);
}

char	*get_next_line(int fd)
{
	static t_list	*p = NULL;
	t_list			*temp;
	char			*buf;

	if (!p) //처음 호출했을 때
	{
		p = ft_lstnew(fd);
		temp = p;
	}
	else //2번째 이상 호출했을 때
	{
		temp = p;
		while (temp->next && temp->fd != fd) //input fd에 해당하는 스레드가 있는지 탐색
			temp = temp->next;
		if (!temp)
			temp = ft_lstnew(fd);
	}
	//리스트 설정 끄읏
	buf = (char *)malloc(BUFFER_SIZE);
	if (fd < 0 || !buf || read(fd, buf, BUFFER_SIZE) == -1
			|| (!buf[0] && temp->fst_call) || !temp)
		return (ft_lstdel(&temp, buf));
	//buf read, 널 체크 및 read 에러 처리 끗
	while (1)
	{
		if (buf[0])
			temp->str = concat(temp->str, buf);
		if (seek_nl(temp->str) >= 0)
			return (get_ret_nl(&temp, buf));
		else if (!read(fd, buf, BUFFER_SIZE) && temp->str[0])
			return (get_ret_nonl(&temp, buf));
		else if (!temp->str[0])
			return (ft_lstdel(&temp, buf));
	}
}