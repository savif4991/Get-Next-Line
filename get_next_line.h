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
	char			*str;
	int				fd;
	struct s_list	*next;
	int				fst_call;
	char			*last_ret;
}	t_list;

t_list			*ft_lstnew(int fd);
void			*ft_lstdel(t_list **lst, char *buf);
void			*ft_memcpy(void *restrict dest, const void *restrict src, unsigned int n);
unsigned int	ft_strlen(const char *s);
char			*get_next_line(int fd);

#endif
