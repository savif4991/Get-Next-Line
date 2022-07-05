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
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size);
unsigned int	ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
char			*append_res(char *res_str, char *buf);
char			*get_next_line(int fd);
int				ft_isascii(int c);


#endif
