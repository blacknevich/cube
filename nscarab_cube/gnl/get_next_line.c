/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 18:00:58 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/14 13:12:36 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			gnl_buf_clear(char **buf)
{
	if (*buf == NULL)
		return (-1);
	free(*buf);
	*buf = NULL;
	return (-1);
}

int			gnl_buf_create(char **buf, long long *read_counter)
{
	if (*buf == NULL)
	{
		*buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (*buf == NULL)
			return (-1);
		if (read_counter)
			*read_counter = 2;
	}
	return (0);
}

long long	gnl_read_old(char **line, char **buf)
{
	char		*buf_pos;
	char		*tmp;

	if ((buf_pos = gnl_ft_strchr(*buf, '\n')))
	{
		if (!(*line = gnl_ft_superstrjoin(*line, *buf)))
			return (-1);
		tmp = *buf;
		*buf = gnl_ft_strdup(++buf_pos);
		free(tmp);
		if (!*buf)
			return (-1);
		return (-2);
	}
	if (!(*line = gnl_ft_superstrjoin(*line, *buf)))
		return (-1);
	tmp = *buf;
	*buf = NULL;
	if (gnl_buf_create(&(*buf), NULL))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (1);
}

long long	gnl_ft_get_new_string(char **line,
		char **buf, long long read_counter)
{
	char	*buf_pos;
	char	*tmp;

	if ((buf_pos = gnl_ft_strchr(*buf, '\n')))
	{
		*line = gnl_ft_superstrjoin(*line, *buf);
		tmp = *buf;
		*buf = gnl_ft_strdup(++buf_pos);
		free(tmp);
		if (!*buf)
			return (-1);
		return (-2);
	}
	if (!(*line = gnl_ft_superstrjoin(*line, *buf)))
		return (-1);
	if (read_counter == 0)
		return (0);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char	*buf[1024];
	long long	read_counter;

	*line = NULL;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	read_counter = 1;
	if (gnl_buf_create(&buf[fd], &read_counter))
		return (gnl_buf_clear(&buf[fd]));
	if (read_counter != 2)
		read_counter = gnl_read_old(line, &buf[fd]);
	while (read_counter > 0)
	{
		read_counter = read(fd, buf[fd], BUFFER_SIZE);
		if (read_counter < 0)
			return (gnl_buf_clear(&buf[fd]));
		buf[fd][read_counter] = '\0';
		read_counter = gnl_ft_get_new_string(line, &buf[fd], read_counter);
	}
	if (read_counter == 0)
		return (gnl_buf_clear(&buf[fd]) + 1);
	if (read_counter == -1)
		return (gnl_buf_clear(&buf[fd]));
	return (1);
}
