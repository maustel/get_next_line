/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:44:40 by maustel           #+#    #+#             */
/*   Updated: 2023/11/23 16:28:05 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
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

	if (s == NULL)			//
		return (0); //
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2, int len)
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

char	*ft_strdup(const char *s, int len)
{
	char	*str;
	int		i;

	str = (char *) malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_memcpy(char *dst, char *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[n] = '\0';
	return (dst);
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
		dst[l] = '\0';
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
