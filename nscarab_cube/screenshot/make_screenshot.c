/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:02:39 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 20:55:10 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

static void	img_to_bmp(t_all *all, int fd)
{
	int	x;
	int	y;

	y = 0;
	while (y < all->parse.res_y)
	{
		x = 0;
		while (x < all->parse.res_x)
		{
			all->render.color = *(int*)(all->mlx.addr +
					(y * all->mlx.line_lenght +
					x * (all->mlx.bits_per_pixel / 8)));
			write(fd, &all->render.color, 4);
			x++;
		}
		y++;
	}
}

static char	*make_bitmap(t_all *all, int fd)
{
	char	*bitmap;

	if (!(bitmap = (char *)ft_calloc(sizeof(char), 54)))
	{
		close(fd);
		exit_with_error("Malloc error", all->parse);
	}
	bitmap[0] = 'B';
	bitmap[1] = 'M';
	*((int*)(bitmap + 2)) = all->parse.res_y * all->parse.res_x * 4 + 54;
	*((int*)(bitmap + 10)) = 54;
	*((int*)(bitmap + 14)) = 40;
	*((int*)(bitmap + 18)) = all->parse.res_x;
	*((int*)(bitmap + 22)) = -all->parse.res_y;
	*(bitmap + 26) = 1;
	*(bitmap + 28) = 32;
	return (bitmap);
}

void		make_screenshot(t_parse *parse)
{
	t_all		all;
	int			fd;
	char		*bitmap;

	all.parse = *parse;
	prep_game(&all);
	prep_graphics(&all);
	raycasting(&all);
	if ((fd = open("screenshot.bmp",
					O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
	{
		close(fd);
		exit_with_error("Can't create screenshot file", *parse);
	}
	bitmap = (char *)make_bitmap(&all, fd);
	write(fd, bitmap, 54);
	free(bitmap);
	img_to_bmp(&all, fd);
	close(fd);
	game_end(&all);
}
