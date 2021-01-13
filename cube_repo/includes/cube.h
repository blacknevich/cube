/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nscarab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:30:34 by nscarab           #+#    #+#             */
/*   Updated: 2021/01/13 21:35:01 by nscarab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# define ESC_KEY 53
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define W_KEY 13
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define MOVESPEED 0.1
# define ROTSPEED 0.03
# define ZOOM 0.6

/*
**------------------------------------------------------------------------
**                             Structures
**------------------------------------------------------------------------
*/
/*
**------------------------------------------------------------------------
**                           MLX structure
**------------------------------------------------------------------------
*/
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
/*
**------------------------------------------------------------------------
**                       Double vector structure
**------------------------------------------------------------------------
*/
typedef struct		s_double_ray
{
	double			x;
	double			y;
}					t_double_ray;
/*
**------------------------------------------------------------------------
**                          Sprite structure
**------------------------------------------------------------------------
*/
typedef struct		s_sprite
{
	double			x;
	double			y;
	double			rel_x;
	double			rel_y;
	double			dist;
}					t_sprite;

/*
**------------------------------------------------------------------------
**                    Parsed information structure
**------------------------------------------------------------------------
*/
typedef struct		s_parse
{
	int				fd;
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
	int				sprite_count;
	t_sprite		**sprites;
	char			**sprites_dist;
}					t_parse;
/*
**------------------------------------------------------------------------
**                     X:Y integral dot structure
**------------------------------------------------------------------------
*/
typedef struct		s_int_dot
{
	int				x;
	int				y;
}					t_int_dot;
/*
**------------------------------------------------------------------------
**                  Rendering information structure
**------------------------------------------------------------------------
*/
typedef struct		s_render
{
	t_double_ray	fan;
	t_double_ray	plane;
	double			camera_x;
	t_double_ray	delta_dist;
	t_double_ray	side_dist;
	double			wall_to_plane;
	int				line_height;
	t_int_dot		map;
	t_int_dot		step;
	double			zoom;
	t_double_ray	pl_dir;
	t_double_ray	pl_pos;
	int				hit;
	int				side;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	int				color;
	double			draw_step;
	double			tex_pos;
	t_double_ray	trans;
	t_int_dot		draw_s;
	t_int_dot		draw_e;
	int				sprite_height;
	int				sprite_width;
	int				sprite_screen;
}					t_render;

/*
**------------------------------------------------------------------------
**                     Texture information structure
**------------------------------------------------------------------------
*/
typedef struct		s_texture
{
	void			*img;
	void			*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
}					t_texture;
/*
**------------------------------------------------------------------------
**                  Structure with different textures
**------------------------------------------------------------------------
*/
typedef struct		s_textures
{
	t_texture		no;
	t_texture		so;
	t_texture		we;
	t_texture		ea;
	t_texture		sprite;
}					t_textures;
/*
**------------------------------------------------------------------------
**                         Keys status structure
**------------------------------------------------------------------------
*/
typedef struct		s_key_status
{
	char			w;
	char			s;
	char			a;
	char			d;
	char			l;
	char			r;
}					t_key_status;

/*
**------------------------------------------------------------------------
**            The big main structure with all other structures
**------------------------------------------------------------------------
*/
typedef struct		s_all
{
	t_parse			parse;
	t_mlx			mlx;
	t_render		render;
	t_textures		textures;
	t_key_status	keys;
}					t_all;

/*
**------------------------------------------------------------------------
**                             Prototypes
**------------------------------------------------------------------------
*/
/*
**------------------------------------------------------------------------
**                              Parsing
**------------------------------------------------------------------------
*/
void				ft_parse(t_parse *parse);
t_parse				create_parse(void);
void				check_premap_string(char *str,
		t_parse *parse, int *ptr_count);
int					get_resolution(char **str, t_parse *parse);
char				*ft_strdup_cube(char **s1, t_parse parse);
int					ft_atoi_resolution(char **str, t_parse parse);
int					ft_atoi_color(char **str, t_parse parse);
int					is_premap(char *file_str);
int					is_map_valid(char **map, t_parse *parse);
int					is_player(int c);
int					is_enough_info(t_parse parse);
int					is_comma(char **str);
void				free_parse(t_parse parse);
void				free_file(char **file);
void				exit_with_error(char *str, t_parse parse);
/*
**------------------------------------------------------------------------
**                            Screenshot
**------------------------------------------------------------------------
*/
void				make_screenshot(t_parse *parse);
/*
**------------------------------------------------------------------------
**                          Game initiation
**------------------------------------------------------------------------
*/
void				game_start(t_parse *parse);
void				prep_game(t_all *all);
void				prep_graphics(t_all *all);
void				print_parse(t_parse parse);
void				init_sprite_texture(char *path, t_all *all);
int					game_end_with_error(char *error, t_all *all);
/*
**------------------------------------------------------------------------
**                          Key processing
**------------------------------------------------------------------------
*/
int					game_end(t_all *all);
int					press_key(int keycode, t_all *all);
int					release_key(int keycode, t_all *all);
void				move_player(t_all *all);
int					no_wall_in_direction(t_all *all, double dir, int axis);
/*
**------------------------------------------------------------------------
**                               Render
**------------------------------------------------------------------------
*/
void				my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void				draw_floor(t_all *all);
void				draw_ceilling(t_all *all);
int					raycasting(t_all *all);
void				render_rays(t_all *all, int x);
void				draw_texture(t_all *all, int x);
void				handle_sprites(t_all *all, double *dist_buff);
void				render_sprites(t_all *all, int count, double *dist_buff);
#endif
