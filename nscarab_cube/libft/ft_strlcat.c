/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:48:47 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/07 13:47:48 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lensrc;
	size_t	lendst;
	size_t	count;

	count = 0;
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (dstsize < lendst)
		return (dstsize + lensrc);
	if (dstsize == 0)
		return (lensrc);
	while (src[count] != '\0' && count + lendst < dstsize - 1)
	{
		dst[count + lendst] = src[count];
		count++;
	}
	dst[count + lendst] = '\0';
	return (lendst + lensrc);
}
