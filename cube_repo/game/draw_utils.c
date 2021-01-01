/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:21:01 by nscarab           #+#    #+#             */
/*   Updated: 2020/12/31 19:41:54 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_lenght + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_ceilling(t_all *all)
{
	size_t	x;
	size_t	y;
	int		color;
	size_t	edge_x;
	size_t	edge_y;

	edge_x = (size_t)(all->parse.res_x);
	edge_y = ((size_t)(all->parse.res_y)) / 2;
	y = 0;
	color = all->parse.ceilling_color;
	while (y < edge_y)
	{
		x = 0;
		while (x < edge_x)
		{
			my_mlx_pixel_put(&all->mlx, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_all *all)
{
	size_t	x;
	size_t	y;
	int	color;

	y = all->parse.res_y / 2;
	color = all->parse.floor_color;
	while (y < (size_t)all->parse.res_y)
	{
		x = 0;
		while (x < (size_t)all->parse.res_x)
		{
			my_mlx_pixel_put(&all->mlx, x, y, color);
			x++;
		}
		y++;
	}
}
