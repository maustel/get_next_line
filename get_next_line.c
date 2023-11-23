/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:41:37 by maustel           #+#    #+#             */
/*   Updated: 2023/11/23 17:52:12 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*write_line(char *rest)
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

static int	endline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*cutline(char *line, char *rest)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	len = ft_strlen(line);
	if (i < len - 1)
	{
		tmp = rest; //
		rest = ft_calloc (len - i + 1, 1);
		free(tmp); //
		ft_memmove(rest, line + i + 1, len - i - 1);
		line[i + 1] = '\0';
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;
	char		*line;
	int			bytes_read;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (rest)
		{
			free (rest);
			rest = NULL;
		}
		return (NULL);
	}
	line = NULL;
	bytes_read = 0;
	if (rest != NULL && ft_strlen(rest) > 0)
		line = write_line(rest);
	if (endline(line) < 1)
	{
		buffer = calloc(BUFFER_SIZE + 1, 1);
		bytes_read = read (fd, buffer, BUFFER_SIZE);
		while ((bytes_read > 0))
		{
			if (line)
			{
				tmp = line;
				line = ft_strjoin(line, buffer, bytes_read);
				free (tmp);
			}
			else
				line = ft_strdup(buffer, bytes_read);
			if (endline(line) == 1)
				break ;
			bytes_read = read (fd, buffer, BUFFER_SIZE);
		}
		free (buffer);
	}
	if (bytes_read < 0 || (bytes_read == 0 && line == NULL))
	{
		free (line);
		free (rest);
		rest = NULL;
		return (NULL);
	}
	if (bytes_read > 0)
		rest = cutline(line, rest);
	return (line);
}

// void	leak (void)
// {
// 	system("leaks a.out");
// }

// int	main()
// {
// 	int		fd = 1;
// 	char	*buf;
// 	// int		bytes_read;

// 	fd = open("amsel", O_RDONLY);
// 	if (fd == -1)
// 		exit(1);
// 	while ((buf = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", buf);
// 		free(buf);
// 	}
// 	// buf = malloc(10);
// 	// free (buf);
// 	// printf("BF = %s\n", buf);
// 	// buf = get_next_line(fd);
// 	// printf("%s", buf);
// 	// free(buf);
// 	// buf = get_next_line(fd);
// 	// printf("%s", buf);
// 	// free(buf);
// 	// buf = get_next_line(fd);
// 	// printf("%s", buf);
// 	// free(buf);

// 	if (close(fd) == -1)
// 		exit(1);
// 	// leak();
// 	return (0);
// }
