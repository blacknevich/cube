#include <mlx.h>

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main ()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int i=5; i<50; i++)
		for ( int j=5; j<50; j++)
			my_mlx_pixel_put(&img, j, i, 0x00FF0000);
	for (int i=15; i<40; i++)
		for ( int j=15; j<40; j++)
			my_mlx_pixel_put(&img, j, i, 0xFF000000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
