/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:50:57 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/07 16:54:49 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"

void	exit_with_error(char *str, t_parse parse)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free_parse(parse);
	exit(1);
}

int	is_extension(char *str, char *ext)
{
	size_t	strlen;
	size_t	extlen;

	strlen = ft_strlen(str);
	extlen = ft_strlen(ext);
	if (extlen > strlen)
		return (0);
	if (extlen == 0)
		return (1);
	if (str[strlen - extlen - 1] != '/')
		if (ft_strncmp(&str[strlen - extlen], ext, extlen))
			return (1);
	return (0);
	}

int				ft_atoi_resolution(char **str, t_parse parse)
{
	long long int	out;

	out = 0;
	skip_spaces(str);
	if (!(ft_isdigit(**str)))
		exit_with_error("Not valid resolution format", parse);
	while (ft_isdigit(**str))
	{
		if (out < 16384)
			out = 10 * out + (**str - '0');
		*str = *str + 1;;
	}
	if (out > 16384)
		out = 16384;
	return (out);
}

int				ft_atoi_color(char **str, t_parse parse)
{
	long long int	out;

	out = 0;
	skip_spaces(str);
	if (!(ft_isdigit(**str)))
		exit_with_error("Not valid color format", parse);
	while (ft_isdigit(**str))
	{
		out = 10 * out + (**str - '0');
		if (out > 255)
			exit_with_error("Not valid color format", parse);
		*str = *str + 1;;
	}
	return (out);
}

void	free_file(char **file)
{
	size_t count;

	count = 0;
	if (file)
	{
		while(file[count])
		{
			free(file[count]);
			file[count++] = NULL;
		}
		free(file);
		file = NULL;
	}
}

void	free_sprites(t_sprite **sprites)
{
	size_t count;

	count = 0;
	if (sprites)
	{
		while(sprites[count])
		{
			free(sprites[count]);
			sprites[count++] = NULL;
		}
		free(sprites);
		sprites = NULL;
	}
}

void	free_parse(t_parse parse)
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
}

char	*ft_strdup_cube(char **s1, t_parse parse)
{
	char	*ptr;
	int		count;
	int		len;

	len = 0;
	count = 0;
	while ((*s1)[count] && (*s1)[count] != ' ')
	{
		count++;
		len++;
	}
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		exit_with_error("Malloc error", parse);
	ptr[len] = '\0';
	count = 0;
	while (len-- > 0)
	{
		ptr[count] = **s1;
		*s1 = *s1 + 1;
		count++;
	}
	return (ptr);
}

int		is_premap(char *file_str)
{
	if (file_str && *file_str != ' ' && *file_str != '0'
			&& *file_str != '1'
			&& *file_str != '2')
		return (1);
	return (0);
}
t_parse	create_parse()
{
	t_parse	parse;

	parse.current_texture = -1;
	parse.res_x = -1;
	parse.res_y = -1;
	parse.floor_color = -1;
	parse.ceilling_color = -1;
	parse.no_texture_path = NULL;
	parse.we_texture_path = NULL;
	parse.so_texture_path = NULL;
	parse.ea_texture_path = NULL;
	parse.sprite_texture_path = NULL;
	parse.player_direction = '\0';
	parse.sprite_count = 0;
	parse.file = NULL;
	return(parse);
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

void	skip_spaces(char **str)
{
	while (**str == ' ')
		*str = *str + 1;
}
