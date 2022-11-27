
#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>
#include <math.h>


#include <mlx.h>

typedef struct s_data {
	void	*img;
	void		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_screen {
	int	top;
	int	left;
	int	width;
	int	height;
	double	scale;
}	t_screen;

void	ft_screen_initialize(t_screen *screen, int width, int height, double scale)
{
	screen->width = width;
	screen->height = height;
	screen->left = 0;
	screen->top = 0;
	screen->scale = scale;
}

int round_int(double d)
{
	int rounded_value;

	rounded_value = (int)(d + 0.01);
	return (rounded_value);
}

void	fractal_put(t_data *data, t_screen screen, int color )
{
	int		iterations;
	int		x_index;
	int		y_index;
	double	c_real = -0.12375;
	double	c_imaginary = 0.56508;
	double z_x;
	double z_y;
	double cx;
	double cy;
	double temp;
	int *dst;
	int h;
	int s;
	int v;

	x_index = 1;
	while (x_index < screen.width)
	{
		y_index = 1;
		while (y_index < screen.height)
		{
			iterations = 1;
			cx = (double)x_index / (double)screen.width * screen.scale + c_real;
			cy = (double)y_index / (double)screen.height * screen.scale + c_imaginary;
			z_x = 0;
			z_y = 0;
			while ((z_x * z_x + z_y * z_y) < 4 && iterations <= 1000)
			{
				temp = z_x * z_x - z_y * z_y + cx;
				z_y = -2 * z_x * z_y + cy;
				z_x = temp;
				iterations++;
			}
			dst = data->addr + (y_index * data->line_length + x_index *  (data->bits_per_pixel / 8));

			h = (int)pow((double)(iterations / 1000) * 360, (double)1.5) % 360;
			s = 100;
			v = round_int((double)iterations / 1000 * 100);
			if ((z_x * z_x + z_y * z_y) < 4)
				*(unsigned int *)dst = color;
			else
				*(unsigned int *)dst = round_int((double)(iterations / (double)1000 * 255 * 255 * 100));
			y_index++;
		}
		x_index++;
	}
}


int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_screen screen;

	ft_screen_initialize(&screen, 700, 500, 2);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, screen.width, screen.height, "Hello world!");
	img.img = mlx_new_image(mlx, screen.width, screen.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	// my_mlx_line_put(&img, 100, 200, 250, 150, 0xFFFFFF);
	fractal_put(&img, screen, 0xFF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
