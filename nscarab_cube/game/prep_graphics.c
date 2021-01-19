/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:42:24 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 21:18:14 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "mlx.h"
#include "libft.h"

static void	init_no_texture(char *path, t_all *all)
{
	t_texture	*no;

	no = &all->textures.no;
	no->img = mlx_xpm_file_to_image(all->mlx.mlx,
			path, &no->width, &no->height);
	if (no->img == NULL)
		game_end_with_error("Can't open north texture", all);
	no->addr = mlx_get_data_addr(no->img, &no->bits_per_pixel,
			&no->line_lenght, &no->endian);
}

static void	init_so_texture(char *path, t_all *all)
{
	t_texture	*so;

	so = &all->textures.so;
	so->img = mlx_xpm_file_to_image(all->mlx.mlx,
			path, &so->width, &so->height);
	if (so->img == NULL)
		game_end_with_error("Can't open south texture", all);
	so->addr = mlx_get_data_addr(so->img, &so->bits_per_pixel,
			&so->line_lenght, &so->endian);
}

static void	init_we_texture(char *path, t_all *all)
{
	t_texture	*we;

	we = &all->textures.we;
	we->img = mlx_xpm_file_to_image(all->mlx.mlx,
			path, &we->width, &we->height);
	if (we->img == NULL)
		game_end_with_error("Can't open west texture", all);
	we->addr = mlx_get_data_addr(we->img, &we->bits_per_pixel,
			&we->line_lenght, &we->endian);
}

static void	init_ea_texture(char *path, t_all *all)
{
	t_texture	*ea;

	ea = &all->textures.ea;
	ea->img = mlx_xpm_file_to_image(all->mlx.mlx,
			path, &ea->width, &ea->height);
	if (ea->img == NULL)
		game_end_with_error("Can't open east texture", all);
	ea->addr = mlx_get_data_addr(ea->img, &ea->bits_per_pixel,
			&ea->line_lenght, &ea->endian);
}

void		prep_graphics(t_all *all)
{
	t_parse *parse;

	parse = &all->parse;
	all->mlx.img = mlx_new_image(all->mlx.mlx, parse->res_x, parse->res_y);
	all->mlx.addr = mlx_get_data_addr(all->mlx.img, &all->mlx.bits_per_pixel,
			&all->mlx.line_lenght, &all->mlx.endian);
	init_no_texture(all->parse.no_texture_path, all);
	init_we_texture(all->parse.we_texture_path, all);
	init_so_texture(all->parse.so_texture_path, all);
	init_ea_texture(all->parse.ea_texture_path, all);
	init_sprite_texture(all->parse.sprite_texture_path, all);
}
