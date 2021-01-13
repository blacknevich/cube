/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_premap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:43:14 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 20:51:06 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"

static int	check_texture(char **str, t_parse *parse)
{
	if (**str == 'N' && *(*str + 1) == 'O' && *(*str + 2) == ' ')
		parse->current_texture = 1;
	else if (**str == 'W' && *(*str + 1) == 'E' && *(*str + 2) == ' ')
		parse->current_texture = 2;
	else if (**str == 'S' && *(*str + 1) == 'O' && *(*str + 2) == ' ')
		parse->current_texture = 3;
	else if (**str == 'E' && *(*str + 1) == 'A' && *(*str + 2) == ' ')
		parse->current_texture = 4;
	else if (**str == 'S' && *(*str + 1) == ' ')
		parse->current_texture = 5;
	else
		return (0);
	if (parse->current_texture == 5)
		*str = *str + 2;
	else if (parse->current_texture > 0)
		*str = *str + 3;
	return (1);
}

static void	get_path(char **str, t_parse *parse)
{
	ft_skip_spaces(str);
	if (parse->current_texture == 1)
		if (parse->no_texture_path != NULL ||
				!(parse->no_texture_path = ft_strdup_cube(str, *parse)))
			exit_with_error("Double info inclusion", *parse);
	if (parse->current_texture == 2)
		if (parse->we_texture_path != NULL ||
				!(parse->we_texture_path = ft_strdup_cube(str, *parse)))
			exit_with_error("Double info inclusion", *parse);
	if (parse->current_texture == 3)
		if (parse->so_texture_path != NULL ||
				!(parse->so_texture_path = ft_strdup_cube(str, *parse)))
			exit_with_error("Double info inclusion", *parse);
	if (parse->current_texture == 4)
		if (parse->ea_texture_path != NULL ||
				!(parse->ea_texture_path = ft_strdup_cube(str, *parse)))
			exit_with_error("Double info inclusion", *parse);
	if (parse->current_texture == 5)
		if (parse->sprite_texture_path != NULL ||
				!(parse->sprite_texture_path = ft_strdup_cube(str, *parse)))
			exit_with_error("Double info inclusion", *parse);
}

static int	check_color(char **str, t_parse *parse)
{
	if (**str == 'F' && *(*str + 1) == ' ')
		parse->current_texture = 1;
	else if (**str == 'C' && *(*str + 1) == ' ')
		parse->current_texture = 2;
	else
		return (0);
	*str = *str + 2;
	return (1);
}

static void	get_color(char **str, t_parse *parse)
{
	int	tmp;
	int	out;

	tmp = ft_atoi_color(str, *parse);
	out = tmp * 65536;
	ft_skip_spaces(str);
	if (!(is_comma(str)))
		exit_with_error("Invalid color format", *parse);
	tmp = ft_atoi_color(str, *parse);
	out = out + tmp * 256;
	ft_skip_spaces(str);
	if (!(is_comma(str)))
		exit_with_error("Invalid color format", *parse);
	tmp = ft_atoi_color(str, *parse);
	out = out + tmp;
	if (parse->current_texture == 1)
		if (parse->floor_color != -1 ||
				(parse->floor_color = out) < 0)
			exit_with_error("Double info inclusion", *parse);
	if (parse->current_texture == 2)
		if (parse->ceilling_color != -1 ||
				(parse->ceilling_color = out) < 0)
			exit_with_error("Double info inclusion", *parse);
}

void		check_premap_string(char *str, t_parse *parse, int *ptr_count)
{
	if (check_texture(&(str), parse))
		get_path(&(str), parse);
	else if (check_color(&(str), parse))
		get_color(&(str), parse);
	else if (*str == 'R' && *(str + 1) == ' ')
		get_resolution(&(str), parse);
	if (*str == '\0')
		*ptr_count = *ptr_count + 1;
	else
		exit_with_error("Invalid configuration format", *parse);
}
