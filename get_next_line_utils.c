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

t_list	*ft_lstnew(int fd)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (ptr == 0)
		return (0);
	ptr->fd = fd;
	ptr->next = 0;
	ptr->content = 0;
	ptr->last_ret = 0;
	return (ptr);
}

void	*ft_lstdel(t_list **lst)
{
	t_list	*temp;

	temp = *lst;
	*lst = temp->next;
	temp->fd = 0;
	temp->next = 0;
	if (temp->content)
		free (temp->content);
	if (temp->last_ret)
		free (temp->last_ret);
	if (temp)
		free (temp);
	return (NULL);
}

t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*adr;

	adr = *lst;
	if (!new)
		return (NULL);
	if (!adr)
	{
		*lst = new;
		return (new);
	}
	while (adr->next)
			adr = adr->next;
	adr->next = new;
	adr = adr->next;
	adr->next = 0;
	return (adr);
}
