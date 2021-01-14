/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:54:39 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/06 10:46:52 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len1;
	size_t	count;

	if (!s1 || !s2)
		return (NULL);
	count = 0;
	len1 = ft_strlen(s1);
	ptr = malloc(len1 + ft_strlen(s2) + 1);
	if (ptr)
	{
		while (s1[count])
		{
			ptr[count] = s1[count];
			count++;
		}
		while (s2[count - len1])
		{
			ptr[count] = s2[count - len1];
			count++;
		}
		ptr[count] = '\0';
		return (ptr);
	}
	return (NULL);
}
