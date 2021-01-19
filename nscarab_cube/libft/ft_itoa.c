/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 11:18:15 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/06 13:07:00 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_posint(int n, int d, int len)
{
	char	*ptr;
	char	*tmp;
	char	sub;

	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	tmp = ptr;
	while (d >= 1)
	{
		sub = n / d + '0';
		*tmp++ = sub;
		n = n % d;
		d = d / 10;
	}
	*tmp = '\0';
	return (ptr);
}

static char	*ft_negint(int n, int d, int len)
{
	char	*ptr;
	char	*tmp;
	char	sub;

	ptr = malloc(len + 2);
	if (!ptr)
		return (NULL);
	tmp = ptr;
	*tmp = '-';
	tmp++;
	while (d >= 1)
	{
		sub = n / d + '0';
		*tmp++ = sub;
		n = n % d;
		d = d / 10;
	}
	*tmp = '\0';
	return (ptr);
}

static char	*ft_subitoa(int n, int sign)
{
	int		d;
	int		len;
	char	*ptr;

	d = 1;
	len = 1;
	while (n / d >= 10)
	{
		d = d * 10;
		len++;
	}
	if (sign < 0)
	{
		ptr = ft_negint(n, d, len);
		return (ptr);
	}
	else
	{
		ptr = ft_posint(n, d, len);
		return (ptr);
	}
}

char		*ft_itoa(int n)
{
	char	*ptr;
	int		sign;

	sign = 1;
	if (n == -2147483648)
	{
		ptr = ft_strdup("-2147483648");
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	ptr = ft_subitoa(n, sign);
	return (ptr);
}
