/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_logic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 21:20:40 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 21:25:30 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	no_wall_in_direction(t_all *all, double dir, int axis)
{
	char		**map;
	t_render	*render;

	map = all->parse.file;
	render = &all->render;
	if (axis == 'x')
	{
		if (map[(int)render->pl_pos.y][(int)(render->pl_pos.x + dir * MOVESPEED
					- 0.1 * (dir < 0) + 0.1 * (dir > 0))] == '0' ||
				is_player(map[(int)render->pl_pos.y][(int)(render->pl_pos.x +
						dir * MOVESPEED - 0.1 * (dir < 0) + 0.1 * (dir > 0))]))
			return (1);
	}
	if (axis == 'y')
		if (map[(int)(render->pl_pos.y + dir * MOVESPEED
					- 0.1 * (dir < 0) + 0.1 * (dir > 0))]
				[(int)render->pl_pos.x] == '0' ||
				is_player(map[(int)(render->pl_pos.y +
						dir * MOVESPEED - 0.1 * (dir < 0) + 0.1 * (dir > 0))]
				[(int)render->pl_pos.x]))
			return (1);
	return (0);
}
