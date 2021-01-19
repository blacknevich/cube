/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:01:24 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 20:45:22 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "mlx.h"
#include "libft.h"
#include <math.h>

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

int		raycasting(t_all *all)
{
	int			x;
	t_render	*render;
	double		dist_buff[all->parse.res_x];

	render = &all->render;
	move_player(all);
	draw_floor(all);
	draw_ceilling(all);
	x = 0;
	while (x < all->parse.res_x)
	{
		render_rays(all, x);
		draw_texture(all, x);
		dist_buff[x] = render->wall_to_plane;
		x++;
	}
	handle_sprites(all, dist_buff);
	if (all->mlx.win)
		mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->mlx.img, 0, 0);
	return (0);
}

void	game_start(t_parse *parse)
{
	t_all		all;

	all.parse = *parse;
	prep_game(&all);
	if (!(all.mlx.win = mlx_new_window(all.mlx.mlx,
					parse->res_x, parse->res_y, "nscarab_cube3D")))
		exit_with_error("MLX can't open window", *parse);
	prep_graphics(&all);
	mlx_do_key_autorepeatoff(all.mlx.mlx);
	mlx_hook(all.mlx.win, 17, 0, game_end, &all);
	mlx_hook(all.mlx.win, 2, 0, press_key, &all);
	mlx_hook(all.mlx.win, 3, 0, release_key, &all);
	mlx_loop_hook(all.mlx.mlx, raycasting, &all);
	mlx_loop(all.mlx.mlx);
}
