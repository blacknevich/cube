/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:42:21 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/02 14:34:21 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	unsigned char		*dst2;
	const unsigned char	*src2;
	unsigned char		c2;

	dst2 = (unsigned char *)dst;
	src2 = (const unsigned char*)src;
	c2 = (unsigned char)c;
	while (len-- > 0)
	{
		if (*src2 == c2)
		{
			*dst2 = *src2;
			return (dst2 + 1);
		}
		*dst2++ = *src2++;
	}
	return (NULL);
}
