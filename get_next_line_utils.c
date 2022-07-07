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

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (ptr == 0)
		return (0);
	ptr->content = content;
	ptr->next = 0;
	return (ptr);
}

void	*ft_lstclear(t_list **lst)
{
	t_list	*adr;
	t_list	*temp;

	adr = *lst;
	temp = adr;
	while (temp != 0)
	{
		adr = adr->next;
		free (adr->content);
		adr->next = 0;
		free (lst);
		temp = adr;
	}
	*lst = 0;
	return (NULL);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*adr;

	adr = *lst;
	if (new == 0)
		return ;
	if (adr == 0)
	{
		adr = new;
		return ;
	}
	while (adr->next != 0)
			adr = adr->next;
	adr->next = new;
	adr = adr->next;
	adr->next = 0;
}
