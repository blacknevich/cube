/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 11:59:51 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/03 12:42:30 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *s2;

	s2 = (char *)s;
	while (*s2)
	{
		if (*s2 == c)
			return (s2);
		s2++;
	}
	if (c == '\0')
		return (s2);
	return (NULL);
}