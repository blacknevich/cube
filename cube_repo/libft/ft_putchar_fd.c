/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:46:26 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/06 12:55:45 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_unicode(char c, int fd)
{
	char byte[2];

	byte[1] = (c & 0x3F) | 0x80;
	byte[0] = ((c & 0xC0) >> 6) | 0xC0;
	write(fd, byte, 2);
	return ;
}

void		ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	if (c < 0)
	{
		ft_unicode(c, fd);
		return ;
	}
	else
		write(fd, &c, 1);
}
