/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:30:34 by nscarab           #+#    #+#             */
/*   Updated: 2020/12/31 16:23:20 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
////////////////////////////////////////don't forget to remove//////////////
#include <stdio.h>


typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
}					t_mlx;

typedef struct		s_parse
{
	int				current_texture;
	int				res_x;
	int				res_y;
	int				floor_color;
	int				ceilling_color;
	char			*no_texture_path;
	char			*we_texture_path;
	char			*so_texture_path;
	char			*ea_texture_path;
	char			*sprite_texture_path;
	char			**file;
	char			player_direction;
	uint32_t		sprite_count;
}					t_parse;

typedef struct		s_all
{
	t_parse			parse;
	t_mlx			mlx;
}					t_all;

void	parse(char **file);
t_parse	create_parse();
int		is_premap(char *file_str);
void	check_premap_string(char *str, t_parse *parse, int *ptr_count);
int		check_texture(char **str, t_parse *parse);
void	get_path(char **str, t_parse *parse);
char	*ft_strdup_cube(char **s1, t_parse parse);
int		check_color(char **str, t_parse *parse);
void	get_color(char **str, t_parse *parse);
int		ft_atoi_resolution(char **str, t_parse parse);
int		ft_atoi_color(char **str, t_parse parse);
int		is_comma(char **str);
void	skip_spaces(char **str);
void	exit_with_error(char *str, t_parse parse);
void	free_parse(t_parse parse);
void	free_file(char **file);
void	print_parse(t_parse parse);
int		check_parse_full(t_parse parse);
int		is_map_valid(char **map, t_parse *parse);
void	game_start(t_parse *parse);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	draw_ceilling(t_all *all);
void	draw_floor(t_all *all);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

#endif
