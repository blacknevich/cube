/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:14:52 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/14 14:55:03 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "mlx.h"
#include "libft.h"

static void	calc_draw_sprite(t_all *all)
{
	t_render	*render;

	render = &all->render;
	render->sprite_height = abs((int)(all->parse.res_y / render->trans.y));
	render->sprite_width = abs((int)(all->parse.res_y / render->trans.y));
	render->draw_s.y = (all->parse.res_y - render->sprite_height) / 2;
	if (render->draw_s.y < 0)
		render->draw_s.y = 0;
	render->draw_e.y = (all->parse.res_y + render->sprite_height) / 2;
	if (render->draw_e.y >= all->parse.res_y)
		render->draw_e.y = all->parse.res_y - 1;
	render->draw_s.x = all->render.sprite_screen - render->sprite_width / 2;
	if (render->draw_s.x < 0)
		render->draw_s.x = 0;
	render->draw_e.x = all->render.sprite_screen + render->sprite_width / 2;
	if (render->draw_e.x >= all->parse.res_x)
		render->draw_e.x = all->parse.res_x - 1;
}

static void	sprite_pixel_put(t_all *all, int x, int y)
{
	t_render	*render;

	render = &all->render;
	render->tex_y = (int)((y - (all->parse.res_y - render->sprite_height) / 2) *
			all->textures.sprite.height / render->sprite_height);
	render->color = ((int*)all->textures.sprite.addr)
		[all->textures.sprite.width * render->tex_y + render->tex_x];
	if ((render->color & 0x00FFFFFF) != 9961608)
		my_mlx_pixel_put(&all->mlx, x, y, render->color);
}

static void	draw_sprite(t_all *all, double *dist_buff)
{
	t_render	*render;
	int			x;
	int			y;

	render = &all->render;
	x = all->render.draw_s.x;
	while (x < render->draw_e.x)
	{
		render->tex_x = (int)((x - (render->sprite_screen
						- render->sprite_width / 2)) *
			all->textures.sprite.width / render->sprite_width);
		if (render->trans.y > 0 && render->trans.y
				< dist_buff[x] && x > 0 && x < all->parse.res_x)
		{
			y = all->render.draw_s.y;
			while (y < render->draw_e.y)
			{
				sprite_pixel_put(all, x, y);
				y++;
			}
		}
		x++;
	}
}

void		render_sprites(t_all *all, int count, double *dist_buff)
{
	double		inv_det;
	t_sprite	**sprites;
	t_render	*render;

	sprites = all->parse.sprites;
	render = &all->render;
	inv_det = 1.0 / (-render->plane.x * render->pl_dir.y
			+ render->pl_dir.x * render->plane.y);
	render->trans.x = inv_det * (render->pl_dir.y *
			sprites[count]->rel_x - render->pl_dir.x *
			sprites[count]->rel_y);
	render->trans.y = inv_det * (render->plane.y *
			sprites[count]->rel_x - render->plane.x *
			sprites[count]->rel_y);
	render->sprite_screen = (int)(all->parse.res_x / 2) *
		(1 + render->trans.x / render->trans.y);
	calc_draw_sprite(all);
	draw_sprite(all, dist_buff);
}
