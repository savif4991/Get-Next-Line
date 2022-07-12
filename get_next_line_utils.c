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
#include "get_next_line.h"

t_list	*ft_lstnew(int fd)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (ptr == 0)
		return (0);
	ptr->fd = fd;
	ptr->next = NULL;
	ptr->str = NULL;
	ptr->fst_call = 1;
	return (ptr);
}

void	*ft_lstdel(t_list **lst, char *buf)
{
	t_list	*temp;

	temp = *lst;
	*lst = temp->next;
	temp->fd = 0;
	temp->next = 0;
	if (temp->last_ret)
		free (temp->last_ret);
	if (temp->str)
		free (temp->str);
	if (temp)
		free (temp);
	if (buf)
		free (buf);
	return (NULL);
}

unsigned int	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *restrict dest, const void *restrict src, unsigned int n)
{
	unsigned int	i;
	char			*temp_d;
	char			*temp_s;

	if (dest == 0 && src == 0)
		return (dest);
	i = 0;
	temp_d = (char *)dest;
	temp_s = (char *)src;
	while (i < n)
	{
		temp_d[i] = temp_s[i];
		i++;
	}
	return (dest);
}