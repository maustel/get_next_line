/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:41:37 by maustel           #+#    #+#             */
/*   Updated: 2023/11/24 10:28:45 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		tmp = rest;
		rest = gnl_calloc (len - i + 1, 1);
		free(tmp);
		ft_memmove(rest, line + i + 1, len - i - 1);
		line[i + 1] = '\0';
	}
	return (rest);
}

static void	readfile(int	*bytes_read, char **line, int fd)
{
	char	*buffer;
	char	*tmp;

	buffer = gnl_calloc(BUFFER_SIZE + 1, 1);
	*bytes_read = read (fd, buffer, BUFFER_SIZE);
	while ((*bytes_read > 0))
	{
		if (*line)
		{
			tmp = *line;
			*line = gnl_strjoin(*line, buffer, *bytes_read);
			free (tmp);
		}
		else
			*line = gnl_strjoin("", buffer, *bytes_read);
		if (endline(*line) == 1)
			break ;
		*bytes_read = read (fd, buffer, BUFFER_SIZE);
	}
	free (buffer);
}

static void	free_rest(char **rest)
{
	free (*rest);
	*rest = NULL;
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (rest)
			free_rest(&rest);
		return (NULL);
	}
	line = NULL;
	bytes_read = 0;
	if (rest != NULL && ft_strlen(rest) > 0)
		line = write_line(rest);
	if (endline(line) < 1)
		readfile(&bytes_read, &line, fd);
	if (bytes_read < 0 || (bytes_read == 0 && line == NULL))
	{
		free (line);
		free_rest(&rest);
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
