/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:49:24 by nscarab           #+#    #+#             */
/*   Updated: 2020/11/07 17:24:19 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		lenght;
	t_list	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	lenght = 1;
	while (tmp->next)
	{
		tmp = tmp->next;
		lenght++;
	}
	return (lenght);
}
