/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:44:40 by maustel           #+#    #+#             */
/*   Updated: 2023/11/30 11:47:55 by maustel          ###   ########.fr       */
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
	line = gnl_calloc(i + 2, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (rest[i] != '\0' && rest[i] != '\n')
	{
		line[i] = rest [i];
		i++;
	}
	line[i] = rest[i];
	if (rest[i] == '\n')
		i++;
	len = gnl_strlen(rest);
	rest = gnl_memmove(rest, rest + i, len - i);
	return (line);
}

void	*gnl_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*p;
	size_t			total_size;

	total_size = count * size;
	if (count && (total_size / count) != size)
		return (NULL);
	p = malloc(count * size);
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

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*gnl_strjoin(char *s1, char *s2, int len)
{
	char	*str;
	int		i;
	int		j;

	str = gnl_calloc (gnl_strlen(s1) + len + 1, 1);
	if (!str)
	{
		if (s1)
			free (s1);
		return (NULL);
	}
	i = 0;
	if (s1)
	{
		j = 0;
		while (s1[j])
			str[i++] = s1[j++];
	}
	j = 0;
	while (s2[j] && j < len)
		str[i++] = s2[j++];
	if (s1)
		free (s1);
	return (str);
}

char	*gnl_memmove(char *dst, char *src, size_t len)
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
