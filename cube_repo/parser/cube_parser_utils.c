/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:50:57 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/14 13:53:31 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "libft.h"

int		ft_atoi_resolution(char **str, t_parse parse)
{
	long long int	out;

	out = 0;
	ft_skip_spaces(str);
	if (!(ft_isdigit(**str)))
		exit_with_error("Not valid resolution format", parse);
	while (ft_isdigit(**str))
	{
		if (out < 2560)
			out = 10 * out + (**str - '0');
		*str = *str + 1;
	}
	if (out > 2560)
		out = 2560;
	return (out);
}

int		ft_atoi_color(char **str, t_parse parse)
{
	long long int	out;

	out = 0;
	ft_skip_spaces(str);
	if (!(ft_isdigit(**str)))
		exit_with_error("Not valid color format", parse);
	while (ft_isdigit(**str))
	{
		out = 10 * out + (**str - '0');
		if (out > 255)
			exit_with_error("Not valid color format", parse);
		*str = *str + 1;
	}
	return (out);
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

t_parse	create_parse(void)
{
	t_parse	parse;

	parse.fd = -1;
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
	parse.sprites = NULL;
	return (parse);
}
