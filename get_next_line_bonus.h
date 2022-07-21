/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:56:39 by daejlee           #+#    #+#             */
/*   Updated: 2022/07/21 16:56:43 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>

typedef struct s_list
{
	char			*str;
	int				fd;
	struct s_list	*next;
	int				fst_call;
	char			*last_ret;
	int				eof_flag;
}	t_list;

t_list			*ft_lstnew(int fd);
void			*ft_lstdel(t_list **lst, char *buf, t_list **p_adr);
unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size);
unsigned int	ft_strlen(const char *s);
char			*concat_buf(char *str, char *buf, int r_flag);
char			*get_next_line(int fd);

#endif
