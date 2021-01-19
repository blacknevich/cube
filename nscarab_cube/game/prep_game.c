/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:48:54 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/19 12:40:58 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "mlx.h"
#include "libft.h"
#include <math.h>

void	take_direction(t_all *all)
{
	if (all->parse.player_direction == 'N')
	{
		all->render.pl_dir.x = 0;
		all->render.pl_dir.y = -1;
	}
	if (all->parse.player_direction == 'S')
	{
		all->render.pl_dir.x = 0;
		all->render.pl_dir.y = 1;
	}
	if (all->parse.player_direction == 'W')
	{
		all->render.pl_dir.x = -1;
		all->render.pl_dir.y = 0;
	}
	if (all->parse.player_direction == 'E')
	{
		all->render.pl_dir.x = 1;
		all->render.pl_dir.y = 0;
	}
	all->render.plane.x = (cos(-1.5708) * all->render.pl_dir.x
			- sin(-1.5708) * all->render.pl_dir.y) * all->render.zoom;
	all->render.plane.y = (sin(-1.5708) * all->render.pl_dir.x
			+ cos(-1.5708) * all->render.pl_dir.y) * all->render.zoom;
}

void	init_player(t_all *all)
{
	char	**map;
	int		x;
	int		y;

	map = all->parse.file;
	all->render.zoom = ZOOM;
	y = 0;
	while ((all->parse.file)[y])
	{
		x = 0;
		while ((all->parse.file)[y][x])
		{
			if (is_player((all->parse.file)[y][x]))
			{
				all->render.pl_pos.x = (double)x + 0.5;
				all->render.pl_pos.y = (double)y + 0.5;
			}
			x++;
		}
		y++;
	}
	take_direction(all);
}

void	init_keys(t_key_status *keys)
{
	keys->a = 0;
	keys->w = 0;
	keys->s = 0;
	keys->d = 0;
	keys->r = 0;
	keys->l = 0;
}

void	prep_game(t_all *all)
{
	init_keys(&all->keys);
	init_player(all);
	all->mlx.win = NULL;
	if (!(all->mlx.mlx = mlx_init()))
		exit_with_error("Can't start MLX", all->parse);
}
