/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:54:25 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/11 18:50:06 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char *cs, char c)
{
	size_t		flag;
	size_t		quantity;

	flag = 1;
	quantity = 0;
	while (*cs)
	{
		if (*cs != c && flag == 1)
		{
			flag = 0;
			quantity++;
		}
		if (*cs == c)
			flag = 1;
		cs++;
	}
	return (quantity);
}

static int		ft_free_mainptr(char **mainptr)
{
	size_t count;

	count = 0;
	while (mainptr[count])
	{
		free(mainptr[count]);
		count++;
	}
	free(mainptr);
	return (1);
}

static char		*ft_fill_subptr(size_t wordcount,
		int wordlenght, char *cs, char **mainptr)
{
	int	i;

	i = 0;
	mainptr[wordcount] = malloc(wordlenght + 1);
	if (!mainptr[wordcount])
		return (NULL);
	cs = cs - wordlenght;
	while (wordlenght-- > 0)
	{
		mainptr[wordcount][i] = cs[i];
		i++;
	}
	mainptr[wordcount][i] = '\0';
	return (mainptr[wordcount]);
}

static int		ft_fill_mainptr(char *cs, char **mainptr, char c)
{
	size_t	wordlenght;
	size_t	wordcount;

	wordcount = 0;
	while (*cs)
	{
		if (*cs != c)
		{
			wordlenght = 0;
			while (*cs && *cs != c)
			{
				cs++;
				++wordlenght;
			}
			if (ft_fill_subptr(wordcount, wordlenght, cs, mainptr) == NULL)
				return (ft_free_mainptr(mainptr));
			wordcount++;
			cs--;
		}
		cs++;
	}
	mainptr[wordcount] = NULL;
	return (0);
}

char			**ft_split(char const *s, char c)
{
	size_t	quantity;
	char	*cs;
	char	**mainptr;
	int		err;

	if (!s)
		return (NULL);
	cs = (char *)s;
	quantity = ft_wordcount(cs, c);
	mainptr = (char **)malloc((quantity + 1) * sizeof(char *));
	if (!mainptr)
	{
		free(mainptr);
		return (NULL);
	}
	err = ft_fill_mainptr(cs, mainptr, c);
	if (err == 1)
		return (NULL);
	else
		return (mainptr);
}
