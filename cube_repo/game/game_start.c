/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:01:24 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/02 16:50:36 by nscarab          ###   ########.fr       */
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

void	draw_line(t_all *all, int x)
{
	int y;

	y = all->render.draw_start;
	while (y < all->render.draw_end)
	{
		my_mlx_pixel_put(&all->mlx, x, y, 9685424);
		y++;
	}
}

int		raycasting(t_all *all)
{
	int		x;
	t_render	*render;

	render = &all->render;
	init_player(all);
	//printf("posx %.2f posy %.2f dirx %.2f diry %.2f planex %.2f planey %.2f", render->pl_pos.x, render->pl_pos.y, render->pl_dir.x, render->pl_dir.y, render->plane.x, render->plane.y);
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
		draw_line(all, x);
		x++;
	}
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->mlx.img, 0, 0);
	return (0);
}

void	game_start(t_parse *parse)
{
	t_all		all;

	all.parse = *parse;
	all.mlx.mlx = mlx_init();
	all.mlx.win = mlx_new_window(all.mlx.mlx, parse->res_x, parse->res_y, "nscarab_cube3D");
	all.mlx.img = mlx_new_image(all.mlx.mlx, parse->res_x , parse->res_y);
	all.mlx.addr = mlx_get_data_addr(all.mlx.img, &all.mlx.bits_per_pixel, &all.mlx.line_lenght, &all.mlx.endian);
	mlx_do_key_autorepeatoff(all.mlx.mlx);
	//init_raycasting(&all);
	mlx_hook(all.mlx.win, 17, 0, game_end, &all);
//	raycasting(&all);
	mlx_loop_hook(all.mlx.mlx, raycasting, &all);
	mlx_loop(all.mlx.mlx);
}
