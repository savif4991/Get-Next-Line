/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:04:40 by daejlee           #+#    #+#             */
/*   Updated: 2022/06/28 15:04:42 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	int				fd;
	struct s_list	*next;
	char			*last_ret;
}	t_list;

unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size);
unsigned int	ft_strlen(const char *s);
t_list			*ft_lstnew(int fd);
void			*ft_lstdel(t_list **lst);
t_list			*ft_lstadd_back(t_list **lst, t_list *new);
char			*get_next_line(int fd);

#endif
