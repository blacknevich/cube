/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:15:32 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 21:29:24 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "mlx.h"
#include "libft.h"
#include <math.h>

static void	move_ws(t_all *all)
{
	t_render	*render;
	char		**map;

	render = &all->render;
	map = all->parse.file;
	if (all->keys.w == 1 && all->keys.s != 1)
	{
		if (no_wall_in_direction(all, render->pl_dir.x, 'x'))
			render->pl_pos.x += render->pl_dir.x * MOVESPEED;
		if (no_wall_in_direction(all, render->pl_dir.y, 'y'))
			render->pl_pos.y += render->pl_dir.y * MOVESPEED;
	}
	if (all->keys.s == 1 && all->keys.w != 1)
	{
		if (no_wall_in_direction(all, -render->pl_dir.x, 'x'))
			render->pl_pos.x -= render->pl_dir.x * MOVESPEED;
		if (no_wall_in_direction(all, -render->pl_dir.y, 'y'))
			render->pl_pos.y -= render->pl_dir.y * MOVESPEED;
	}
}

static void	move_ad(t_all *all)
{
	t_render	*render;
	char		**map;

	render = &all->render;
	map = all->parse.file;
	if (all->keys.a == 1 && all->keys.d != 1)
	{
		if (no_wall_in_direction(all, render->plane.x, 'x'))
			render->pl_pos.x += render->plane.x * MOVESPEED;
		if (no_wall_in_direction(all, render->plane.y, 'y'))
			render->pl_pos.y += render->plane.y * MOVESPEED;
	}
	if (all->keys.d == 1 && all->keys.a != 1)
	{
		if (no_wall_in_direction(all, -render->plane.x, 'x'))
			render->pl_pos.x -= render->plane.x * MOVESPEED;
		if (no_wall_in_direction(all, -render->plane.y, 'y'))
			render->pl_pos.y -= render->plane.y * MOVESPEED;
	}
}

static void	move_r(t_all *all)
{
	t_render	*render;
	char		**map;
	double		old_dir_x;

	render = &all->render;
	map = all->parse.file;
	if (all->keys.r == 1 && all->keys.l != 1)
	{
		old_dir_x = render->pl_dir.x;
		render->pl_dir.x = render->pl_dir.x * cos(ROTSPEED)
			- render->pl_dir.y * sin(ROTSPEED);
		render->pl_dir.y = old_dir_x * sin(ROTSPEED)
			+ render->pl_dir.y * cos(ROTSPEED);
		all->render.plane.x = (cos(-1.5708) * all->render.pl_dir.x
				- sin(-1.5708) * all->render.pl_dir.y) * all->render.zoom;
		all->render.plane.y = (sin(-1.5708) * all->render.pl_dir.x
				+ cos(-1.5708) * all->render.pl_dir.y) * all->render.zoom;
	}
}

static void	move_l(t_all *all)
{
	t_render	*render;
	char		**map;
	double		old_dir_x;

	render = &all->render;
	map = all->parse.file;
	if (all->keys.l == 1 && all->keys.r != 1)
	{
		old_dir_x = render->pl_dir.x;
		render->pl_dir.x = render->pl_dir.x * cos(-ROTSPEED)
			- render->pl_dir.y * sin(-ROTSPEED);
		render->pl_dir.y = old_dir_x * sin(-ROTSPEED)
			+ render->pl_dir.y * cos(-ROTSPEED);
		all->render.plane.x = (cos(-1.5708) * all->render.pl_dir.x
				- sin(-1.5708) * all->render.pl_dir.y) * all->render.zoom;
		all->render.plane.y = (sin(-1.5708) * all->render.pl_dir.x
				+ cos(-1.5708) * all->render.pl_dir.y) * all->render.zoom;
	}
}

void		move_player(t_all *all)
{
	if (all->keys.w == 0 && all->keys.a == 0 && all->keys.s == 0 &&
			all->keys.d == 0 && all->keys.r == 0 && all->keys.l == 0)
		return ;
	move_ws(all);
	move_ad(all);
	move_r(all);
	move_l(all);
}
