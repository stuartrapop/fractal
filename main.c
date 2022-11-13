
#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>
#include <math.h>


#include <mlx.h>

typedef struct	s_data {
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	round_int(double d)
{
	int rounded_value;

	rounded_value = (int)(d + 0.01);
	return (rounded_value);
}

void	my_mlx_cirle_put(t_data *data, int center_x, int center_y, int color)
{
	int	*dst;
	double x;
	double y;
	int b;
	int c;

	x = 5.0;
	b = -2 * center_y;
	while (x < 400.0)
	{
		c = (center_y * center_y) - 40 * 40 + (x - center_x) * (x - center_x);
		y = -b/2 + sqrt(b * b - 4 * c)/2;

	
		dst = data->addr + (round_int(y) * data->line_length  + round_int(x) * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
		y = -b/2 - sqrt(b * b - 4 * c)/2;
			dst = data->addr + (round_int(y) * data->line_length  + round_int(x) * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
		x = x + 0.01;
	}
}

void	my_mlx_line_put(t_data *data, int start_x, int start_y, int end_x, int end_y , int color)
{
	int	*dst;
	float index;
	double x;
	double y;

	index = 0;
	while (index < 500)
	{
		x = (double)start_x * 1.0 + (end_x - start_x) * (index / 500);
		y = (double)start_y * 1.0 + (end_y - start_y) * (index / 500);
		dst = data->addr + (round_int(y) * data->line_length + round_int(x) * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
		index = index + 1.0;
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	printf(" address %p\n", img.addr);
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = (int *) mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	printf("bits per pixel %d\n", img.bits_per_pixel);
	printf("line length %d\n", img.line_length);
	printf("endian %d\n", img.endian);
	my_mlx_cirle_put(&img, 100, 100, 0xFFFFFF);
	my_mlx_cirle_put(&img, 150, 150, 0xFFFFFF);
	my_mlx_line_put(&img, 100, 200, 250, 150, 0xFFFFFF);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
