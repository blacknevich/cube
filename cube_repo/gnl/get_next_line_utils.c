/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:55:50 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/18 19:37:24 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*gnl_ft_strchr(char *s, int c)
{
	char	*s2;

	s2 = s;
	while (*s2)
	{
		if (*s2 == c)
		{
			return (s2);
		}
		s2++;
	}
	if (c == '\0')
		return (s2);
	return (NULL);
}

long long	gnl_ft_strlen_n(char *s)
{
	size_t len;

	if (!s)
		return (0);
	len = 0;
	while (*s && *s != '\n')
	{
		len++;
		s++;
	}
	return (len);
}

long long	gnl_ft_strlen(char *s)
{
	long long	len;

	if (!s)
		return (0);
	len = 0;
	while (*s++)
	{
		len++;
	}
	return (len);
}

char		*gnl_ft_strdup(char *s1)
{
	char		*ptr;
	long long	count;

	count = 0;
	ptr = (char*)malloc(BUFFER_SIZE + 1);
	if (!ptr)
		return (NULL);
	while (s1[count])
	{
		ptr[count] = s1[count];
		count++;
	}
	ptr[count] = '\0';
	return (ptr);
}

char		*gnl_ft_superstrjoin(char *s1, char *s2)
{
	char		*ptr;
	long long	len1;
	char		*out;
	char		*s1_pos;

	len1 = gnl_ft_strlen(s1);
	if (!(ptr = (char*)malloc(len1 + gnl_ft_strlen_n(s2) + 1)))
		return (NULL);
	out = ptr;
	s1_pos = s1;
	while (s1 && *s1)
		*ptr++ = *s1++;
	while (s2 && *s2 && *s2 != '\n')
		*ptr++ = *s2++;
	*ptr = '\0';
	if (s1_pos)
		free(s1_pos);
	return (out);
}
