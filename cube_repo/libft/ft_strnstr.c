/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:42:29 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/10 13:05:55 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char *hay;

	hay = (char *)haystack;
	if (*needle == '\0')
		return (hay);
	while (*hay && len > 0)
	{
		if (len < ft_strlen(needle))
			return (NULL);
		if (ft_strncmp(hay, needle, ft_strlen(needle)) == 0)
			return (hay);
		hay++;
		len--;
	}
	return (NULL);
}
