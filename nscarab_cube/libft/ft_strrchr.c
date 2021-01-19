/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:44:14 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/03 16:40:34 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s2;
	size_t	counter;

	s2 = (char *)s;
	counter = 0;
	while (*s2)
	{
		s2++;
		counter++;
	}
	if (c == '\0')
		return (s2);
	while (counter-- > 0)
	{
		s2--;
		if (*s2 == c)
			return (s2);
	}
	return (NULL);
}
