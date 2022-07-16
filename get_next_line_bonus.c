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
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

static int	seek_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\n')
	{
		i++;
		if (!str[i])
			return (-1);
	}
	return (i);
}

static char	*get_ret_nl(t_list **targ_adr, char *buf, t_list **head_adr)
{
	char	*ret;
	t_list	*target;
	int		nl_idx;
	char	*temp;

	free (buf);
	target = *targ_adr;
	nl_idx = seek_nl(target->str);
	ret = (char *)malloc(nl_idx + 2);
	temp = (char *)malloc(ft_strlen(target->str) - nl_idx + 1);
	if (!ret || !temp)
		return (ft_lstdel(targ_adr, buf, head_adr));
	ft_strlcpy(ret, target->str, nl_idx + 2);
	ft_strlcpy(temp, target->str + nl_idx + 1,
		ft_strlen(target->str) - nl_idx + 1);
	free (target->str);
	target->str = temp;
	if (target->last_ret)
		free (target->last_ret);
	target->last_ret = ret;
	return (ret);
}

static char	*get_ret_nonl(t_list **targ_adr, char *buf, t_list **head_adr)
{
	char	*ret;
	t_list	*target;

	free (buf);
	target = *targ_adr;
	ret = (char *)malloc(ft_strlen(target->str) + 1);
	if (!ret)
		return (ft_lstdel(targ_adr, buf, head_adr));
	ft_strlcpy(ret, target->str, ft_strlen(target->str) + 1);
	if (target->last_ret)
		free (target->last_ret);
	target->last_ret = ret;
	target->flag = 1;
	return (ret);
}

static char	*get_ret(int r_flag, t_list **targ_adr,
		char *buf, t_list **head_adr)
{
	t_list	*target;

	target = *targ_adr;
	while (1)
	{
		if (r_flag == -1 || target->flag || (target->fst_call && !buf[0])
			|| (!r_flag && !target->str[0]))
			return (ft_lstdel(targ_adr, buf, head_adr));
		else if (r_flag)
			target->str = concat_buf(target->str, buf, r_flag);
		target->fst_call = 0;
		if (seek_nl(target->str) >= 0)
			return (get_ret_nl(targ_adr, buf, head_adr));
		r_flag = read(target->fd, buf, BUFFER_SIZE);
		if (!r_flag && target->str[0])
			return (get_ret_nonl(targ_adr, buf, head_adr));
	}
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	t_list			*target;
	char			*buf;
	int				r_flag;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	r_flag = read(fd, buf, BUFFER_SIZE);
	if (fd < 0 || !buf || r_flag == -1 || (!r_flag && !head))
		return (ft_lstdel(NULL, buf, &head));
	buf[r_flag] = '\0';
	if (!head)
		head = ft_lstnew(fd);
	target = head;
	if (!head->fst_call)
	{
		while (target->fd != fd && target->next)
			target = target->next;
		if (!target->next && target->fd != fd)
		{
			target->next = ft_lstnew(fd);
			target = target->next;
		}
	}
	return (get_ret(r_flag, &target, buf, &head));
}
