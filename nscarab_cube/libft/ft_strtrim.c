/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:52:48 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/06 11:07:04 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_endtrim(char const *s1, char const *set, char *s2)
{
	char	*s3;
	char	*set2;
	size_t	flag;

	s3 = (char *)(s1 + ft_strlen(s1) - 1);
	flag = 1;
	while (flag == 1 && s3 >= s2)
	{
		flag = 0;
		set2 = (char *)set;
		while (*set2)
		{
			if (*set2 == *s3)
			{
				s3--;
				flag = 1;
			}
			set2++;
		}
	}
	return (s3);
}

static char	*ft_begintrim(char const *s1, char const *set)
{
	char	*s2;
	char	*set2;
	size_t	flag;

	s2 = (char *)s1;
	flag = 1;
	while (flag == 1)
	{
		flag = 0;
		set2 = (char *)set;
		while (*set2)
		{
			if (*set2 == *s2)
			{
				s2++;
				flag = 1;
			}
			set2++;
		}
	}
	return (s2);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	char	*s2;
	char	*s3;
	char	*tmp;

	if (!s1)
		return (NULL);
	s2 = ft_begintrim(s1, set);
	s3 = ft_endtrim(s1, set, s2);
	ptr = malloc((s3 - s2) + 2);
	if (ptr)
	{
		tmp = ptr;
		while (s2 <= s3)
			*tmp++ = *s2++;
		*tmp = '\0';
		return (ptr);
	}
	return (NULL);
}
