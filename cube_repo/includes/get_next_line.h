/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 17:54:12 by nscarab           #+#    #+#             */
/*   Updated: 2020/12/17 19:51:20 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# define BUFFER_SIZE 1024

int			get_next_line(int fd, char **line);
int			gnl_buf_create(char **buf, long long *read_counter);
int			gnl_buf_clear(char **buf);
long long	gnl_read_old(char **line, char **buf);
char		*gnl_ft_strchr(char *s, int c);
long long	gnl_ft_get_new_string(char **line,
		char **buf, long long read_counter);
long long	gnl_ft_strlen_n(char *s);
long long	gnl_ft_strlen(char *s);
char		*gnl_ft_strdup(char *s1);
char		*gnl_ft_superstrjoin(char *s1, char *s2);

#endif
