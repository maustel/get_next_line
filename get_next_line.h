/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:42:21 by maustel           #+#    #+#             */
/*   Updated: 2023/11/24 10:28:23 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

# include <stdio.h>
# include <fcntl.h>
//for open() and close() in the main

char			*get_next_line(int fd);
char			*write_line(char *rest);
void			*gnl_calloc(size_t count, size_t size);
unsigned long	ft_strlen(const char *s);
char			*gnl_strjoin(char const *s1, char const *s2, int len);
char			*ft_memmove(char *dst, char *src, size_t len);

#endif
