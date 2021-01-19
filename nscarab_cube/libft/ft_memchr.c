/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:42:38 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/02 17:38:36 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s2;
	unsigned char		c2;

	s2 = (const unsigned char*)s;
	c2 = (unsigned char)c;
	while (n--)
	{
		if (*s2 == c2)
		{
			return ((unsigned char*)s2);
		}
		s2++;
	}
	return (NULL);
}
