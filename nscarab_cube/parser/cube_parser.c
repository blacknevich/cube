/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:51:18 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/14 13:53:22 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"

static void	get_sprite_dot(t_parse *parse, uint32_t count,
		uint32_t x, uint32_t y)
{
	if (!(parse->sprites[count] = (t_sprite*)
				malloc(sizeof(t_sprite))))
		exit_with_error("Malloc error", *parse);
	parse->sprites[count]->x = (double)x + 0.5;
	parse->sprites[count]->y = (double)y + 0.5;
}

static void	init_sprites(t_parse *parse)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	count;

	y = 0;
	count = 0;
	parse->sprites = (t_sprite**)malloc(sizeof(t_sprite*) *
			(parse->sprite_count + 1));
	if (!parse->sprites)
		exit_with_error("Malloc error", *parse);
	while (parse->file[y])
	{
		x = 0;
		while (parse->file[y][x])
		{
			if (parse->file[y][x] == '2')
				get_sprite_dot(parse, count++, x, y);
			x++;
		}
		y++;
	}
	parse->sprites[count] = NULL;
}

int			get_resolution(char **str, t_parse *parse)
{
	if (parse->res_x != -1 || parse->res_y != -1)
		exit_with_error("Double info inclusion", *parse);
	*str = *str + 2;
	if ((parse->res_x = ft_atoi_resolution(str, *parse)) <= 0)
		exit_with_error("Invalid resolution", *parse);
	if ((parse->res_y = ft_atoi_resolution(str, *parse)) <= 0)
		exit_with_error("Invalid resolution", *parse);
	if (parse->res_y > 1440)
		parse->res_y = 1440;
	return (0);
}

static char	**cut_premap(char **file, int map_pos, t_parse *parse)
{
	char	**map;
	int		filesize;
	int		count;

	filesize = 0;
	count = 0;
	while (file[filesize])
		filesize++;
	if (!(map = (char **)malloc(sizeof(char *) * (filesize - map_pos + 1))))
		exit_with_error("Malloc error", *parse);
	while (file[map_pos])
	{
		map[count] = ft_strdup(file[map_pos]);
		if (!map[count])
		{
			free_file(map);
			exit_with_error("Malloc error", *parse);
		}
		map_pos++;
		count++;
	}
	map[count] = NULL;
	free_file(file);
	return (map);
}

void		ft_parse(t_parse *parse)
{
	int	count;

	count = 0;
	if ((parse->file)[count][0] == '\0')
		exit_with_error("First line is empty", *parse);
	while (is_premap((parse->file)[count]))
		check_premap_string((parse->file)[count], parse, &count);
	if (!is_enough_info(*parse))
		exit_with_error("Not enough map information", *parse);
	parse->file = cut_premap(parse->file, count, parse);
	is_map_valid(parse->file, parse);
	init_sprites(parse);
}
