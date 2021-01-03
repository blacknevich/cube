/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:01:24 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/03 20:47:43 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube.h"
#include "mlx.h"
#include "libft.h"
# include <math.h>

int	game_end(t_all *all)
{
	mlx_destroy_window(all->mlx.mlx, all->mlx.win);
	free_parse(all->parse);
	//sleep(60);
	exit(0);
	return (0);
}

int	game_end_with_error(char *error, t_all *all)
{
	mlx_destroy_window(all->mlx.mlx, all->mlx.win);
	//sleep(60);
	exit_with_error(error, all->parse);
	return (1);
}

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
}
void	init_player(t_all *all)
{
	char	**map;
	int		x;
	int		y;

	map = all->parse.file;
	all->render.zoom = 0.66;
	y = 0;
	while ((all->parse.file)[y])
	{
		x = 0;
		while((all->parse.file)[y][x])
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
	all->render.plane.x = (cos(-1.5708) * all->render.pl_dir.x - sin(-1.5708) * all->render.pl_dir.y) * all->render.zoom;
	all->render.plane.y = (sin(-1.5708) * all->render.pl_dir.x + cos(-1.5708) * all->render.pl_dir.y) * all->render.zoom;
}

void	init_side_dist(t_all *all)
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

void	find_wall(t_all *all)
{
	t_render	*render;

	render = &all->render;
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

void	project_on_plane(t_all *all)
{
	t_render	*render;

	render = &all->render;
	if (render->side == 0)
		render->wall_to_plane = (render->map.x - render->pl_pos.x + (1 - render->step.x) / 2) / render->fan.x;
	else
	{
		render->wall_to_plane = (render->map.y - render->pl_pos.y + (1 - render->step.y) / 2) / render->fan.y;
	}
}

void	calc_line(t_all *all)
{
	t_render	*render;

	render = &all->render;
	render->line_height = (int)(all->parse.res_y / render->wall_to_plane);

	render->draw_start = (all->parse.res_y - render->line_height) / 2;
	if(render->draw_start < 0)
		render->draw_start = 0;
	render->draw_end = (render->line_height + all->parse.res_y) / 2;
	if(render->draw_end >= all->parse.res_y)
		render->draw_end = all->parse.res_y - 1;
}

t_texture	*choose_texture(t_all *all)
{
	t_render	*render;

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

void	render_texture(t_all *all, t_texture *drawn)
{
	t_render	*render;

	render = &all->render;
	if (render->side == 0)
		render->wall_x = render->pl_pos.y + render->wall_to_plane * render->fan.y;
	else
		render->wall_x = render->pl_pos.x + render->wall_to_plane * render->fan.x;
	render->wall_x -= floor(render->wall_x);
	render->tex_x = (int)(render->wall_x * (double)(drawn->width));
	if (render->side == 1 && render->fan.y > 0)
		render->tex_x = drawn->width - render->tex_x - 1;
	if (render->side == 0 && render->fan.x < 0)
		render->tex_x = drawn->width - render->tex_x - 1;
	render->draw_step = 1.0 * drawn->height / render->line_height;
	render->tex_pos = (render->draw_start - all->parse.res_y / 2
			+ render->line_height / 2) * render->draw_step;
	//printf("wallx %.2f, tex_x %d, draw_step %.2f, tex_pos %.2f",
	//		render->wall_x, render->tex_x, render->draw_step, render->tex_pos);
}
void	draw_texture(t_all *all, int x)
{
	int			y;
	t_texture	*drawn;
	int			color;
	int			tex_y;
	drawn = choose_texture(all);
	//printf("img %p, addr %p, width %d,  height %d,  bpp %d, l_lght %d, endian %d", 
			//drawn->img, drawn->addr, drawn->width, drawn->height, drawn->bits_per_pixel, drawn->line_lenght, drawn->endian);
	render_texture(all, drawn);
	y = all->render.draw_start;
	/*if (all->render.tex_pos > (double)(drawn->height - 1))
		tex_y = drawn->height - 1;
	else
		tex_y = (int)all->render.tex_pos;
		*/
	while (y < all->render.draw_end)
	{
		tex_y = (int)all->render.tex_pos;
		all->render.tex_pos += all->render.draw_step;
		color = ((int*)drawn->addr)[drawn->height * tex_y + all->render.tex_x];
		my_mlx_pixel_put(&all->mlx, x, y, color);
		y++;
	}
}

void	move_player(t_all *all)
{
	t_render	render;
	char		**map;

	render = &all->render;
	map = &all->parse.file;
	if (all->keys.w == 0 && all->keys.a == 0 && all->keys.s == 0 &&
			all->keys.d == 0 && all->keys.r == 0 &&all->keys.l == 0)
		return ;
	if (all->keys.w == 1)
	{
		if (is_wall
	}

}

int		raycasting(t_all *all)
{
	int		x;
	t_render	*render;

	render = &all->render;
	init_player(all);
	//printf("posx %.2f posy %.2f dirx %.2f diry %.2f planex %.2f planey %.2f", render->pl_pos.x, render->pl_pos.y, render->pl_dir.x, render->pl_dir.y, render->plane.x, render->plane.y);
	move_player(all);
	draw_floor(all);
	draw_ceilling(all);
	x = 0;
	while (x < all->parse.res_x)
	{
		render->camera_x = 2 * (all->parse.res_x - x) / (double)(all->parse.res_x) - 1;
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
//		printf("fanx %.2f, fany %.2f\n, mapx %d, mapy %d, deltax %.2f, deltay %f, sidex %.2f, sidey %.2f\n stepx %d,  stepy %d, wallperp %.2f", render->fan.x, render->fan.y, render->map.x,  render->map.y, render->delta_dist.x,  render->delta_dist.y, render->side_dist.x, render->side_dist.y, render->step.x, render->step.y, render->wall_to_plane);
		calc_line(all);
		//printf("line_height %d, draw start %d, draw end %d\n, resolution %d", render->line_height, render->draw_start, render->draw_end, all->parse.res_y);
		draw_texture(all, x);
		x++;
	}
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->mlx.img, 0, 0);
	return (0);
}

void	init_no_texture(char *path, t_all *all)
{
	t_texture	*no;

	no = &all->textures.no;
	no->img = mlx_xpm_file_to_image(all->mlx.mlx, path, &no->width, &no->height);
	if (no->img == NULL)
		game_end_with_error("Can't open north texture", all);
	no->addr = mlx_get_data_addr(no->img, &no->bits_per_pixel,
			&no->line_lenght, &no->endian);
}

void	init_so_texture(char *path, t_all *all)
{
	t_texture	*so;

	so = &all->textures.so;
	so->img = mlx_xpm_file_to_image(all->mlx.mlx, path, &so->width, &so->height);
	if (so->img == NULL)
		game_end_with_error("Can't open south texture", all);
	so->addr = mlx_get_data_addr(so->img, &so->bits_per_pixel,
			&so->line_lenght, &so->endian);
}

void	init_we_texture(char *path, t_all *all)
{
	t_texture	*we;

	we = &all->textures.we;
	we->img = mlx_xpm_file_to_image(all->mlx.mlx, path, &we->width, &we->height);
	if (we->img == NULL)
		game_end_with_error("Can't open west texture", all);
	we->addr = mlx_get_data_addr(we->img, &we->bits_per_pixel,
			&we->line_lenght, &we->endian);
}

void	init_ea_texture(char *path, t_all *all)
{
	t_texture	*ea;

	ea = &all->textures.ea;
	ea->img = mlx_xpm_file_to_image(all->mlx.mlx, path, &ea->width, &ea->height);
	if (ea->img == NULL)
		game_end_with_error("Can't open east texture", all);
	ea->addr = mlx_get_data_addr(ea->img, &ea->bits_per_pixel,
			&ea->line_lenght, &ea->endian);
}

void	init_sprite_texture(char *path, t_all *all)
{
	t_texture	*sprite;

	sprite = &all->textures.sprite;
	sprite->img = mlx_xpm_file_to_image(all->mlx.mlx, path,
			&sprite->width, &sprite->height);
	if (sprite->img == NULL)
		game_end_with_error("Can't open sprite texture", all);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
			&sprite->line_lenght, &sprite->endian);
}

void	init_textures(t_all *all)
{
	init_no_texture(all->parse.no_texture_path, all);
	init_we_texture(all->parse.we_texture_path, all);
	init_so_texture(all->parse.so_texture_path, all);
	init_ea_texture(all->parse.ea_texture_path, all);
	init_sprite_texture(all->parse.sprite_texture_path, all);
}

int 	press_key(int keycode, t_all *ll)
{
	if (keycode == ESC_KEY)
		end_game(all);
	if (keycode == A_KEY)
		all->keys.a = 1;
	if (keycode == W_KEY)
		all->keys.w = 1;
	if (keycode == S_KEY)
		all->keys.s = 1;
	if (keycode == D_KEY)
		all->keys.d = 1;
	if (keycode == RIGHT_KEY)
		all->keys.r = 1;
	if (keycode == LEFT_KEY)
		all->keys.l = 1;
}

int 	release_key(int keycode, t_all *ll)
{
	if (keycode == A_KEY)
		all->keys.a = 0;
	if (keycode == W_KEY)
		all->keys.w = 0;
	if (keycode == S_KEY)
		all->keys.s = 0;
	if (keycode == D_KEY)
		all->keys.d = 0;
	if (keycode == RIGHT_KEY)
		all->keys.r = 0;
	if (keycode == LEFT_KEY)
		all->keys.l = 0;
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

void	game_start(t_parse *parse)
{
	t_all		all;

	all.parse = *parse;
	all.mlx.mlx = mlx_init();
	all.mlx.win = mlx_new_window(all.mlx.mlx, parse->res_x, parse->res_y, "nscarab_cube3D");
	all.mlx.img = mlx_new_image(all.mlx.mlx, parse->res_x , parse->res_y);
	all.mlx.addr = mlx_get_data_addr(all.mlx.img, &all.mlx.bits_per_pixel, &all.mlx.line_lenght, &all.mlx.endian);
	init_textures(&all);
	init_keys(&all->keys);
	mlx_do_key_autorepeatoff(all.mlx.mlx);
	mlx_hook(all.mlx.win, 17, 0, game_end, &all);
	mlx_hook(all.mlx.win, 2, 0, press_key, &all);
	mlx_hook(all.mlx.win, 3, 0, release_key, &all);
//	raycasting(&all);
	mlx_loop_hook(all.mlx.mlx, raycasting, &all);
/*t_texture *we;
we = &all.textures.we;
	all.textures.we.img = mlx_xpm_file_to_image(all.mlx.mlx, all.parse.we_texture_path, &all.textures.we.width, &all.textures.we.height);
	all.textures.we.addr = mlx_get_data_addr(all.textures.we.img, &all.textures.we.bits_per_pixel,
			&all.textures.we.line_lenght, &all.textures.we.endian);
	int y = 0;
	int x = 0;
	int color;
while (y < we->height)
{
	x = 0;
	while (x < we->width)
	{
		color = ((int*)we->addr)[we->height * y + x];
		my_mlx_pixel_put(&all.mlx, x, y, color);
		my_mlx_pixel_put(&all.mlx, x, y + 64, color);
x++;
	}
	y++;
}
*/
	mlx_put_image_to_window(all.mlx.mlx, all.mlx.win, all.mlx.img, 0, 0);
	mlx_loop(all.mlx.mlx);
}
