/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:28:51 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 21:18:48 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

static void	lstadd_back_safe(t_list **begin, char *line, t_parse parse)
{
	t_list	*tmp;

	if (!(tmp = ft_lstnew(line)))
	{
		ft_lstclear(begin, free);
		exit_with_error("Malloc error", parse);
	}
	ft_lstadd_back(begin, tmp);
}

static char	**list_to_arr(t_list **begin, int size, t_parse *parse)
{
	int		count;
	t_list	*tmp;
	char	**file;

	count = 0;
	if (!(file = (char **)malloc(sizeof(char *) * (size + 1))))
	{
		ft_lstclear(begin, free);
		exit_with_error("Malloc error", *parse);
	}
	tmp = *begin;
	while (tmp)
	{
		if (!(file[count++] = ft_strdup(tmp->content)))
			exit_with_error("Malloc error", *parse);
		tmp = tmp->next;
	}
	file[count] = NULL;
	return (file);
}

static void	read_file(int fd, t_list **begin, t_parse *parse)
{
	char	*line;
	int		check;

	line = NULL;
	while ((check = get_next_line(fd, &line)))
	{
		if (check == -1)
		{
			if (line)
				free(line);
			exit_with_error("Gnl error", *parse);
		}
		lstadd_back_safe(begin, line, *parse);
	}
	if (ft_strlen(line) > 0)
		lstadd_back_safe(begin, line, *parse);
	else
		free(line);
}

int			is_extension(char *str, char *ext)
{
	size_t	strlen;
	size_t	extlen;

	if (!str)
		return (0);
	strlen = ft_strlen(str);
	extlen = ft_strlen(ext);
	if (extlen >= strlen)
		return (0);
	if (extlen == 0)
		return (1);
	if (str[strlen - extlen - 1] != '/')
		if (!ft_strncmp(&(str[strlen - extlen]), ext, extlen))
			return (1);
	return (0);
}

int			main(int argc, char **argv)
{
	t_list	*begin;
	t_parse	parse;

	parse = create_parse();
	if (argc == 1 || argc > 3)
		exit_with_error("Invalid number of arguments", parse);
	if (!is_extension(argv[1], ".cub"))
		exit_with_error("Invalid map extension", parse);
	if ((parse.fd = open(argv[1], O_RDONLY)) == -1)
		exit_with_error("Can't open map", parse);
	begin = NULL;
	read_file(parse.fd, &begin, &parse);
	parse.file = list_to_arr(&begin, ft_lstsize(begin), &parse);
	ft_lstclear(&begin, free);
	ft_parse(&parse);
	if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "--save", ft_strlen(argv[2]) + 1))
			make_screenshot(&parse);
		else
			exit_with_error("Invalid flag", parse);
	}
	game_start(&parse);
	return (0);
}
