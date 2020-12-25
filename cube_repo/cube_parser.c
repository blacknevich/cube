/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:51:18 by nscarab           #+#    #+#             */
/*   Updated: 2020/12/25 16:40:39 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft/libft.h"


int	check_texture(char **str, t_parse *parse)
{
	if (**str == 'N' && *(*str + 1) == 'O' && *(*str + 2)  == ' ')
		parse->current_texture = 1;
	else if (**str == 'W' && *(*str + 1) == 'E' && *(*str + 2)  == ' ')
		parse->current_texture = 2;
	else if (**str == 'S' && *(*str + 1) == 'O' && *(*str + 2)  == ' ')
		parse->current_texture = 3;
	else if (**str == 'E' && *(*str + 1) == 'A' && *(*str + 2)  == ' ')
		parse->current_texture = 4;
	else if (**str == 'S' && *(*str + 1)  == ' ')
		parse->current_texture = 5;
	else
		return (0);
	if (parse->current_texture == 5)
		*str = *str + 2;
	else if (parse->current_texture > 0)
		*str = *str + 3;
	return (1);
}

int	check_color(char **str, t_parse *parse)
{
	if (**str == 'F' && *(*str + 1)  == ' ')
		parse->current_texture = 1;
	else if (**str == 'C' && *(*str + 1)  == ' ')
		parse->current_texture = 2;
	else
		return (0);
	*str = *str + 2;
	return (1);
}

void	get_path(char **str, t_parse *parse)
{
	skip_spaces(str);
	if (parse->current_texture == 1)
		if(parse->no_texture_path != NULL ||
				!(parse->no_texture_path = ft_strdup_cube(str, *parse)))
			exit_with_error("Double info inclusion", *parse);
	if (parse->current_texture == 2)
		if(parse->we_texture_path != NULL ||
				!(parse->we_texture_path = ft_strdup_cube(str, *parse)))
			exit_with_error("Double info inclusion", *parse);
	if (parse->current_texture == 3)
		if(parse->so_texture_path != NULL ||
				!(parse->so_texture_path = ft_strdup_cube(str, *parse)))
			exit_with_error("Double info inclusion", *parse);
	if (parse->current_texture == 4)
		if(parse->ea_texture_path != NULL ||
				!(parse->ea_texture_path = ft_strdup_cube(str, *parse)))
			exit_with_error("Double info inclusion", *parse);
	if (parse->current_texture == 5)
		if(parse->sprite_texture_path != NULL ||
				!(parse->sprite_texture_path = ft_strdup_cube(str, *parse)))
			exit_with_error("Double info inclusion", *parse);
}

int	get_resolution(char **str, t_parse *parse)
{
	if(parse->res_x != -1 || parse->res_y != -1)
		exit_with_error("Double info inclusion", *parse);
	*str = *str + 2;
	if ((parse->res_x = ft_atoi_resolution(str, *parse)) < 0)
		return (1);
	if ((parse->res_y = ft_atoi_resolution(str, *parse)) < 0)
		return (1);
	return (0);
}

void	get_color(char **str, t_parse *parse)
{
	int	tmp;
	int	out;

	tmp = ft_atoi_color(str, *parse);
	out = tmp * 65536;
	skip_spaces(str);
	if (!(is_comma(str)))
		exit_with_error("Invalid color format", *parse);
	tmp = ft_atoi_color(str, *parse);
	out = out + tmp * 256;
		skip_spaces(str);
	if (!(is_comma(str)))
		exit_with_error("Invalid color format", *parse);
	tmp = ft_atoi_color(str, *parse);
	out = out + tmp;
	if (parse->current_texture == 1)
		if(parse->floor_color != -1 ||
				(parse->floor_color = out) < 0)
			exit_with_error("Double info inclusion", *parse);
	if (parse->current_texture == 2)
		if(parse->ceilling_color != -1 ||
				(parse->ceilling_color = out) < 0)
			exit_with_error("Double info inclusion", *parse);
}

int	check_parse_full(t_parse parse)
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
		return (1);
	return(0);
}

void	print_parse(t_parse parse)
{
	printf("\n|||%d|||", parse.current_texture);
	printf("\n|||%d|||", parse.res_x);
	printf("\n|||%d|||", parse.res_y);
	printf("\n|||%d|||", parse.floor_color);
	printf("\n|||%d|||", parse.ceilling_color);
	printf("\n|||%s|||", parse.no_texture_path);
	printf("\n|||%s|||", parse.we_texture_path);
	printf("\n|||%s|||", parse.so_texture_path);
	printf("\n|||%s|||", parse.ea_texture_path);
	printf("\n|||%s|||", parse.sprite_texture_path);
}

char	**cut_premap(char **file, int map_pos, t_parse *parse)
{
	char	**map;
	int		filesize;
	int		count;

	filesize = 0;
	count = 0;
	while(file[filesize])
		filesize++;
	if (!(map = (char **)malloc(sizeof(char *) * (filesize - map_pos + 1))))
		exit_with_error("Malloc error", *parse);
	while (file[map_pos])
	{
		map[count] = ft_strdup(file[map_pos]);
		if (!map[count])
		{
			free_file(map);
			exit_with_error("Malloc error", *parse);
		}
		map_pos++;
		count++;
	}
	map[count] = NULL;
	free_file(file);
	return (map);
}

void	check_premap_string(char *str, t_parse *parse, int *ptr_count)
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

void	parse(char **file)
{
	int	count;
	t_parse	parse;

	count = 0;
	parse = create_parse();
	parse.file = file;
	while (is_premap(file[count]))
		check_premap_string(file[count], &parse, &count);
	if (check_parse_full(parse))
		exit_with_error("Not enough map information", parse);
	parse.file = cut_premap(file, count, &parse);
	////////////////////remove///////////////////////////////////
	//print_parse(parse);
	count = 0;
	while((parse.file)[count])
		ft_putendl_fd((parse.file)[count++], 1);
	////////////////////////////////////////////////////////////
	is_map_valid(parse.file, &parse);
	free_parse(parse);
	sleep(60);
}
