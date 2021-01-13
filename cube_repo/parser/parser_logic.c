/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:27:40 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 20:42:39 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdlib.h>

int	is_premap(char *file_str)
{
	if (file_str && *file_str != ' ' && *file_str != '0'
			&& *file_str != '1'
			&& *file_str != '2')
		return (1);
	return (0);
}

int	is_player(int c)
{
	if (c == 'N' || c == 'E'
			|| c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	is_enough_info(t_parse parse)
{
	if (parse.res_x == -1 ||
	parse.res_y == -1 ||
	parse.floor_color == -1 ||
	parse.ceilling_color == -1 ||
	parse.no_texture_path == NULL ||
	parse.we_texture_path == NULL ||
	parse.so_texture_path == NULL ||
	parse.ea_texture_path == NULL ||
	parse.sprite_texture_path == NULL)
		return (0);
	return (1);
}

int	is_comma(char **str)
{
	if (**str == ',')
	{
		*str = *str + 1;
		return (1);
	}
	return (0);
}
