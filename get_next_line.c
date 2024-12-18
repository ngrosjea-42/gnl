/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrosjea <ngrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:33:35 by ngrosjea          #+#    #+#             */
/*   Updated: 2024/12/17 13:26:00 by ngrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_line(char *buf, int bytes)
{
	int	i;

	i = 0;
	while (i < bytes)
	{
		if (buf[i] == '\n')
			return (++i);
		i++;
	}
	return (0);
}

static char	*sub_alread_read(char *buf, int bytes, int already_read)
{
	int	i;

	i = 0;
	while (i < bytes - already_read)
	{
		buf[i] = buf[i + already_read];
		i++;
	}
	return (buf);
}

static void	ft_free_all(char **buf, char *line, int *bytes)
{
	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (bytes)
		*bytes = 0;
}

static char	*get_one_line(char **buf, int *bytes, int fd)
{
	int		already_read;
	char	*line;

	line = NULL;
	already_read = 0;
	while (*bytes > 0)
	{
		if (check_line(*buf, *bytes))
		{
			already_read = check_line(*buf, *bytes);
			line = ft_strjoin(line, *buf, already_read);
			if (!line)
				return (ft_free_all(buf, line, NULL), NULL);
			*buf = sub_alread_read(*buf, *bytes, already_read);
			*bytes = *bytes - already_read;
			return (line);
		}
		line = ft_strjoin(line, *buf, *bytes);
		if (!line)
			return (ft_free_all(buf, line, bytes), NULL);
		*bytes = read(fd, *buf, BUFFER_SIZE);
	}
	if (*bytes == -1)
		return (ft_free_all(buf, line, bytes), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;
	static int	bytes;

	if (!buf)
		buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (NULL);
	line = NULL;
	if (bytes == 0)
		bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes <= 0)
		return (ft_free_all(&buf, NULL, &bytes), NULL);
	if (bytes > 0)
		line = get_one_line(&buf, &bytes, fd);
	return (line);
}
