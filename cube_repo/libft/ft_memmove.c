/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:37:45 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/07 18:22:25 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst2;
	const char	*src2;

	dst2 = dst;
	src2 = src;
	if (!src && !dst)
		return (dst);
	if (dst2 < src2)
	{
		while (len--)
		{
			*dst2++ = *src2++;
		}
	}
	else
	{
		while (len--)
		{
			dst2[len] = src2[len];
		}
	}
	return (dst);
}
