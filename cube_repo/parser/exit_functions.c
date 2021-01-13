/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:21:24 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 20:44:07 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>

void		free_file(char **file)
{
	size_t count;

	count = 0;
	if (file)
	{
		while (file[count])
		{
			free(file[count]);
			file[count++] = NULL;
		}
		free(file);
		file = NULL;
	}
}

static void	free_sprites(t_sprite **sprites)
{
	size_t count;

	count = 0;
	if (sprites)
	{
		while (sprites[count])
		{
			free(sprites[count]);
			sprites[count++] = NULL;
		}
		free(sprites);
		sprites = NULL;
	}
}

void		free_parse(t_parse parse)
{
	if (parse.no_texture_path)
		free(parse.no_texture_path);
	if (parse.we_texture_path)
		free(parse.we_texture_path);
	if (parse.so_texture_path)
		free(parse.so_texture_path);
	if (parse.ea_texture_path)
		free(parse.ea_texture_path);
	if (parse.sprite_texture_path)
		free(parse.sprite_texture_path);
	free_file(parse.file);
	free_sprites(parse.sprites);
	if (parse.fd != -1 && parse.fd != 0)
		close(parse.fd);
}

void		exit_with_error(char *str, t_parse parse)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free_parse(parse);
	exit(1);
}

int			game_end_with_error(char *error, t_all *all)
{
	if (all->mlx.win)
		mlx_destroy_window(all->mlx.mlx, all->mlx.win);
	exit_with_error(error, all->parse);
	return (1);
}
