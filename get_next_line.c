/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:41:37 by maustel           #+#    #+#             */
/*   Updated: 2024/04/25 08:59:16 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_rest(char **rest, char **line)
{
	if (*rest)
		free (*rest);
	if (*line)
		free (*line);
	*rest = NULL;
	*line = NULL;
	return (NULL);
}

static int	endline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

static char	*cutline(char *buffer, char **rest, int *len)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (buffer[i] != '\n' && (buffer[i] != '\0'))
		i++;
	if (i < *len - 1)
	{
		if (rest)
		{
			tmp = *rest;
			*rest = gnl_calloc (*len - i + 1, sizeof (char *));
			free(tmp);
		}
		else
			*rest = gnl_calloc (*len - i + 1, sizeof (char *));
		if (!*rest)
			return (free(buffer), NULL);
		gnl_memmove(*rest, buffer + i + 1, *len - i - 1);
		*len = i + 1;
		buffer[i + 1] = '\0';
	}
	return (buffer);
}

static char	*readfile(int	*bytes_read, char *line, int fd, char **rest)
{
	char	*buffer;
	int		len;

	buffer = gnl_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (free_rest(rest, &line));
	*bytes_read = read (fd, buffer, BUFFER_SIZE);
	while ((*bytes_read > 0))
	{
		len = *bytes_read;
		if (endline(buffer) == 1)
			buffer = cutline(buffer, rest, &len);
		if (!buffer)
			return (free_rest(rest, &line));
		line = gnl_strjoin(line, buffer, len);
		if (!line || endline(line) == 1)
			break ;
		*bytes_read = read (fd, buffer, BUFFER_SIZE);
	}
	return (free (buffer), line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	int			bytes_read;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_rest(&rest, &line));
	bytes_read = 0;
	if (rest != NULL && gnl_strlen(rest) > 0)
	{
		line = write_line(rest);
		if (!line)
			return (free_rest(&rest, &line));
	}
	if (endline(line) < 1)
	{
		line = readfile(&bytes_read, line, fd, &rest);
		if (!line)
			return (free_rest(&rest, &line));
	}
	if (bytes_read < 0 || (bytes_read == 0 && line == NULL))
		return (free_rest(&rest, &line));
	return (line);
}

// void	leak (void)
// {
// 	system("leaks a.out");
// }

// int	main()
// {
// 	int		fd = -1;
// 	char	*line;

// 	fd = open("amsel", O_RDONLY);
// 	if (fd == -1)
// 		exit(1);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	if (close(fd) == -1)
// 		exit(1);
// 	// leak();
// 	return (0);
// }
