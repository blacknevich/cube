/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:38:27 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/02 18:08:54 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *cs1;
	const unsigned char *cs2;

	cs1 = (const unsigned char *)s1;
	cs2 = (const unsigned char *)s2;
	while (n-- > 0)
	{
		if (*cs1++ != *cs2++)
			return (cs1[-1] - cs2[-1]);
	}
	return (0);
}
