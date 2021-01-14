/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:10:06 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/07 14:20:41 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	count;

	if (!s)
		return (NULL);
	count = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	ptr = malloc(len + 1);
	if (ptr)
	{
		while (s[count])
		{
			if (count >= start && count < start + len)
				ptr[count - start] = s[count];
			count++;
		}
		ptr[len] = '\0';
		return (ptr);
	}
	return (NULL);
}
