/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:01:24 by nscarab           #+#    #+#             */
/*   Updated: 2020/12/31 17:45:22 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube.h"
#include "mlx.h"

void	game_start(t_parse *parse)
{
	t_all		all;

	all.parse = *parse;

	all.mlx.mlx = mlx_init();
	all.mlx.win = mlx_new_window(all.mlx.mlx, parse->res_x, parse->res_y, "nscarab_cube3D");
	all.mlx.img = mlx_new_image(all.mlx.mlx, parse->res_x , parse->res_y);
	all.mlx.addr = mlx_get_data_addr(all.mlx.img, &all.mlx.bits_per_pixel, &all.mlx.line_lenght, &all.mlx.endian);
	//my_mlx_pixel_put(&all.mlx, 20, 20, parse->ceilling_color);
	draw_floor(&all);
	draw_ceilling(&all);
	mlx_put_image_to_window(all.mlx.mlx, all.mlx.win, all.mlx.img, 0, 0);
	mlx_loop(all.mlx.mlx);
}
