/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:32:45 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/04 16:41:23 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *ptr;

	ptr = malloc(ft_strlen(s1) + 1);
	if (ptr)
		ft_memcpy(ptr, s1, ft_strlen(s1) + 1);
	return (ptr);
}
