/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:27:38 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/06 12:50:02 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		spacehelp(char *str)
{
	int spacecount;

	spacecount = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\v' || *str == '\f' || *str == '\r')
	{
		++str;
		++spacecount;
	}
	return (spacecount);
}

int				ft_atoi(const char *str)
{
	long long int	out;
	int				sign;
	char			*str2;

	out = 0;
	sign = 1;
	str2 = (char *)str;
	str2 = str2 + spacehelp(str2);
	if (*str2 == '-' || *str2 == '+')
	{
		if (*str2 == '-')
			sign = -1;
		++str2;
	}
	while ((*str2 >= '0') && (*str2 <= '9'))
	{
		if (out > 922337203685477580 && *str2 > '7'
				&& *str2 <= '9' && sign == 1)
			return (-1);
		if (out > 922337203685477580 && *str2 == '9' && sign == -1)
			return (0);
		out = 10 * out + (*str2 - '0');
		++str2;
	}
	return (out * sign);
}
