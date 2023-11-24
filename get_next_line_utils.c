/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:44:40 by maustel           #+#    #+#             */
/*   Updated: 2023/11/24 10:28:15 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*write_line(char *rest)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	while (rest[i] != '\0' && rest[i] != '\n')
		i++;
	line = ft_calloc(i + 2, 1);
	i = 0;
	while (rest[i] != '\0' && rest[i] != '\n')
	{
		line[i] = rest [i];
		i++;
	}
	if (rest[i] == '\n' || rest[i] == '\0')
	{
		line[i] = rest[i];
		if (rest[i] == '\n')
			i++;
	}
	len = ft_strlen(rest);
	rest = ft_memmove(rest, rest + i, len - i);
	return (line);
}

void	*gnl_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*p;

	if (count * size > 2147483647)
		return (NULL);
	p = (void *) malloc(count * size);
	if (!p)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

unsigned long	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*gnl_strjoin(char const *s1, char const *s2, int len)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(s1) + len;
	str = (char *) malloc (sizeof(const char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] && j < len)
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	*ft_memmove(char *dst, char *src, size_t len)
{
	size_t	l;

	l = len;
	if (src < dst)
	{
		while (len > 0)
		{
			dst[len - 1] = src[len - 1];
			len --;
		}
	}
	else
	{
		if (!dst && !src)
			return (NULL);
		len = 0;
		while (len < l)
		{
			dst[len] = src[len];
			len++;
		}
	}
	dst[l] = '\0';
	return (dst);
}
