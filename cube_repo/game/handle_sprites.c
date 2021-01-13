/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:08:16 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 21:02:06 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "mlx.h"
#include "libft.h"

static void	sort_sprites(t_sprite **sprites, int num)
{
	int			i;
	int			j;
	t_sprite	*save;

	if (num == 0)
		return ;
	i = 0;
	while (i < num - 1)
	{
		j = i + 1;
		while (j < num)
		{
			if (sprites[i]->dist < sprites[j]->dist)
			{
				save = sprites[i];
				sprites[i] = sprites[j];
				sprites[j] = save;
			}
			j++;
		}
		i++;
	}
}

static void	calc_sprite_distance(t_all *all)
{
	t_sprite		**sprites;
	int				count;

	sprites = all->parse.sprites;
	count = 0;
	while (sprites[count])
	{
		sprites[count]->rel_x = -all->render.pl_pos.x +
			sprites[count]->x;
		sprites[count]->rel_y = -all->render.pl_pos.y +
			sprites[count]->y;
		sprites[count]->dist = sprites[count]->rel_x *
			sprites[count]->rel_x +
			sprites[count]->rel_y * sprites[count]->rel_y;
		count++;
	}
}

void		handle_sprites(t_all *all, double *dist_buff)
{
	int			count;
	t_sprite	**sprites;
	t_render	*render;

	sprites = all->parse.sprites;
	count = 0;
	render = &all->render;
	calc_sprite_distance(all);
	sort_sprites(all->parse.sprites, all->parse.sprite_count);
	while (sprites[count])
	{
		render_sprites(all, count, dist_buff);
		count++;
	}
}
