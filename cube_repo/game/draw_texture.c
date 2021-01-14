/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:28:27 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/14 14:42:44 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "mlx.h"
#include "libft.h"
#include <math.h>

static t_texture	*choose_texture(t_all *all)
{
	t_render		*render;

	render = &all->render;
	if (render->side == 1)
	{
		if (render->fan.y < 0)
			return (&all->textures.no);
		else
			return (&all->textures.so);
	}
	else
	{
		if (render->fan.x < 0)
			return (&all->textures.ea);
		else
			return (&all->textures.we);
	}
}

static void			render_texture(t_all *all, t_texture *drawn)
{
	t_render		*render;

	render = &all->render;
	if (render->side == 0)
		render->wall_x = render->pl_pos.y
			+ render->wall_to_plane * render->fan.y;
	else
		render->wall_x = render->pl_pos.x
			+ render->wall_to_plane * render->fan.x;
	render->wall_x -= floor(render->wall_x);
	render->tex_x = (int)(render->wall_x * (double)(drawn->width));
	if (render->side == 1 && render->fan.y > 0)
		render->tex_x = drawn->width - render->tex_x - 1;
	if (render->side == 0 && render->fan.x < 0)
		render->tex_x = drawn->width - render->tex_x - 1;
	render->draw_step = 1.0 * drawn->height / render->line_height;
	render->tex_pos = (render->draw_start - all->parse.res_y / 2
			+ render->line_height / 2) * render->draw_step;
}

void				draw_texture(t_all *all, int x)
{
	int				y;
	t_texture		*drawn;
	int				color;
	int				tex_y;

	drawn = choose_texture(all);
	render_texture(all, drawn);
	y = all->render.draw_start;
	while (y < all->render.draw_end)
	{
		tex_y = (int)all->render.tex_pos;
		if (tex_y > all->parse.res_y)
			tex_y = all->parse.res_y;
		all->render.tex_pos += all->render.draw_step;
		color = ((int*)drawn->addr)[drawn->width * tex_y + all->render.tex_x];
		my_mlx_pixel_put(&all->mlx, x, y, color);
		y++;
	}
}
