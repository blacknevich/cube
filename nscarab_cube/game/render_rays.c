/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:53:03 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 21:13:12 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "mlx.h"
#include "libft.h"
#include <math.h>

static void	calc_line(t_all *all)
{
	t_render	*render;

	render = &all->render;
	render->line_height = (int)(all->parse.res_y / render->wall_to_plane);
	render->draw_start = (all->parse.res_y - render->line_height) / 2;
	if (render->draw_start < 0)
		render->draw_start = 0;
	render->draw_end = (render->line_height + all->parse.res_y) / 2;
	if (render->draw_end >= all->parse.res_y)
		render->draw_end = all->parse.res_y - 1;
}

static void	project_on_plane(t_all *all)
{
	t_render	*render;

	render = &all->render;
	if (render->side == 0)
		render->wall_to_plane = (render->map.x - render->pl_pos.x
				+ (1 - render->step.x) / 2) / render->fan.x;
	else
	{
		render->wall_to_plane = (render->map.y - render->pl_pos.y
				+ (1 - render->step.y) / 2) / render->fan.y;
	}
	if (render->wall_to_plane == 0)
		render->wall_to_plane += 0.05;
}

static void	find_wall(t_all *all)
{
	t_render	*render;

	render = &all->render;
	if (all->parse.file[render->map.y][render->map.x] == '1')
		render->hit = 1;
	while (render->hit == 0)
	{
		if (render->side_dist.x < render->side_dist.y)
		{
			render->side_dist.x += render->delta_dist.x;
			render->map.x += render->step.x;
			render->side = 0;
		}
		else
		{
			render->side_dist.y += render->delta_dist.y;
			render->map.y += render->step.y;
			render->side = 1;
		}
		if (all->parse.file[render->map.y][render->map.x] == '1')
			render->hit = 1;
	}
}

static void	init_side_dist(t_all *all)
{
	if (all->render.fan.x < 0)
	{
		all->render.step.x = -1;
		all->render.side_dist.x = (all->render.pl_pos.x
				- all->render.map.x) * all->render.delta_dist.x;
	}
	else
	{
		all->render.step.x = 1;
		all->render.side_dist.x = (all->render.map.x +
				1.0 - all->render.pl_pos.x) * all->render.delta_dist.x;
	}
	if (all->render.fan.y < 0)
	{
		all->render.step.y = -1;
		all->render.side_dist.y = (all->render.pl_pos.y
				- all->render.map.y) * all->render.delta_dist.y;
	}
	else
	{
		all->render.step.y = 1;
		all->render.side_dist.y = (all->render.map.y +
				1.0 - all->render.pl_pos.y) * all->render.delta_dist.y;
	}
}

void		render_rays(t_all *all, int x)
{
	t_render	*render;

	render = &all->render;
	render->camera_x = 2 * (all->parse.res_x - x) /
		(double)(all->parse.res_x) - 1;
	render->fan.x = render->pl_dir.x + render->plane.x * render->camera_x;
	render->fan.y = render->pl_dir.y + render->plane.y * render->camera_x;
	render->map.x = (int)render->pl_pos.x;
	render->map.y = (int)render->pl_pos.y;
	render->delta_dist.x = fabs(1 / render->fan.x);
	render->delta_dist.y = fabs(1 / render->fan.y);
	init_side_dist(all);
	render->hit = 0;
	find_wall(all);
	project_on_plane(all);
	calc_line(all);
}
