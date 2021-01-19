/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:04:54 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 20:02:16 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "mlx.h"
#include "libft.h"
#include <math.h>

int	game_end(t_all *all)
{
	if (all->mlx.win)
		mlx_destroy_window(all->mlx.mlx, all->mlx.win);
	free_parse(all->parse);
	exit(0);
	return (0);
}

int	press_key(int keycode, t_all *all)
{
	if (keycode == ESC_KEY)
		game_end(all);
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
	return (0);
}

int	release_key(int keycode, t_all *all)
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
	return (0);
}
