/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:28:51 by nscarab           #+#    #+#             */
/*   Updated: 2020/12/31 15:25:00 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include "get_next_line.h"

char	**buf_file(t_list **begin, int size)
{
	int count;
	t_list	*tmp;
	char	**file;

	count = 0;
	if(!(file = (char **)malloc(sizeof(char *) * (size + 1))))
	{
		ft_lstclear(begin, NULL);
		return (NULL);
	}
	tmp = *begin;
	while(tmp)
	{
		if (!(file[count++] = ft_strdup(tmp->content)))
		{
			free_file(file);
			write(2, "Error\nMalloc error\n", 19);
			exit(1);
		}
		tmp = tmp->next;
	}
	file[count] = NULL;
	return (file);
}

int main(int argc, char **argv)
{
	int 		fd;
	char		*line;
	t_list		*begin;
	char		**file;

	if (argc > 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	line = NULL;
	begin = NULL;
	while (get_next_line(fd, &line))
		ft_lstadd_back(&begin, ft_lstnew(line));
	if (ft_strlen(line) > 0)
		ft_lstadd_back(&begin, ft_lstnew(line)); 
	else
		free(line);
	file = buf_file(&begin, ft_lstsize(begin));
	ft_lstclear(&begin, free);
	parse(file);
	return (0);
}
