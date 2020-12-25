/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_of_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:47:36 by nscarab           #+#    #+#             */
/*   Updated: 2020/12/25 16:08:36 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft/libft.h"

int	is_player(int c)
{
	if (c == 'N' || c == 'E'
			|| c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	is_interior(int c)
{
	if (is_player(c) || c == '0' || c =='2')
		return (1);
	return(0);
}

int	is_outside(int c)
{
	if (c == ' ' || c == '\0')
		return (1);
	return(0);
}

void	check_valid_exterior(uint32_t int_i, uint32_t int_j, t_parse *parse)
{
	if (is_interior((parse->file)[int_i][int_j + 1]))
		exit_with_error("Map not closed", *parse);
	if ((parse->file)[int_i + 1] &&
			ft_strlen((parse->file)[int_i + 1]) >= int_j &&
			is_interior((parse->file)[int_i + 1][int_j]))
		exit_with_error("Map not closed", *parse);
}

void	check_valid_interior(uint32_t int_i, uint32_t int_j, t_parse *parse)
{
	if (int_i == 0 || int_j == ft_strlen((parse->file)[int_i])
				|| int_j == 0 || !(parse->file)[int_i + 1])
		exit_with_error("Map not closed", *parse);
	if (ft_strlen((parse->file)[int_i - 1]) < (int_j + 1))
		exit_with_error("Map not closed", *parse);
	if (is_outside((parse->file)[int_i][int_j + 1]))
		exit_with_error("Map not closed", *parse);
	if (ft_strlen((parse->file)[int_i + 1]) < (int_j + 1)
			 || is_outside((parse->file)[int_i + 1][int_j]))
		exit_with_error("Map not closed", *parse);
	if ((parse->file)[int_i][int_j] == '2')
		parse->sprite_count = parse->sprite_count + 1;
	if (is_player((parse->file)[int_i][int_j]))
	{
		if (parse->player_direction)
			exit_with_error("More then one player", *parse);
		parse->player_direction = (parse->file)[int_i][int_j];
	}
}

int	is_map_valid(char **map, t_parse *parse)
{
	uint32_t	int_i;
	uint32_t	int_j;

	int_i = 0;
	while (map[int_i])
	{
		int_j = 0;
		if (map[int_i][int_j] == '\0')
			exit_with_error("Map with empty line", *parse);
		while (map[int_i][int_j])
		{
			if (is_interior(map[int_i][int_j]))
				check_valid_interior(int_i, int_j, parse);
			else if (map[int_i][int_j] == ' ')
				check_valid_exterior(int_i, int_j, parse);
			else if (map[int_i][int_j] != '1')
				exit_with_error("Invalid map symbol", *parse);
			int_j++;
		}
		int_i++;
	}
	if (parse->player_direction == '\0')
		exit_with_error("No player on map", *parse);
	return (1);
}
