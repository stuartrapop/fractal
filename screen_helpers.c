/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:33:29 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/07 10:37:20 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include "constants.h"

void	initialize(t_fractal *fractal)
{
	fractal->screen.width = SCREEN_WIDTH;
	fractal->screen.height = SCREEN_HEIGHT;
	fractal->screen.name = SCREEN_NAME;
	fractal->screen.x_offset = -SCREEN_WIDTH / 2;
	fractal->screen.y_offset = -SCREEN_HEIGHT / 2;
	fractal->screen.pan_start_x = 0;
	fractal->screen.pan_start_y = 0;
	fractal->screen.mouse_x = 0;
	fractal->screen.mouse_y = 0;
	fractal->screen.mouse_down = 0;
	fractal->screen.scale = 1;
	fractal->mlx = mlx_init();
	fractal->mlx_win = mlx_new_window(fractal->mlx, fractal->screen.width, \
		fractal->screen.height, fractal->screen.name);
	fractal->img.img = mlx_new_image(fractal->mlx, fractal->screen.width, \
		fractal->screen.height);
	fractal->img.addr = mlx_get_data_addr(fractal->img.img, \
		&fractal->img.bits_per_pixel, &fractal->img.line_length, \
		&fractal->img.endian);
}

int	destroy_window(t_fractal *fractal)
{
	fractal->screen.width = 800;
	mlx_destroy_image(fractal->mlx, fractal->img.img);
	mlx_destroy_window(fractal->mlx, fractal->mlx_win);
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	*dst;

	dst = data->addr + (y * data->line_length + \
				x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	screen_to_world(t_screen_point *s_point, t_world_point *w_point, \
	t_screen screen)
{
	w_point->x = (double)((s_point->x / screen.scale + screen.x_offset));
	w_point->y = (double)((s_point->y / screen.scale + screen.y_offset));
}

void	world_to_screen(t_screen_point *s_point, t_world_point *w_point, \
	t_screen screen)
{
	s_point->x = (int)((w_point->x - screen.x_offset) * screen.scale);
	s_point->y = (int)((w_point->y - screen.y_offset) * screen.scale);
}
