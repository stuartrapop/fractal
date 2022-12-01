/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:33:29 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/01 17:39:38 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include "keycode.h"

void	initialize(t_fractal *fractal)
{
	fractal->screen.width = SCREEN_WIDTH;
	fractal->screen.height = SCREEN_HEIGHT;
	fractal->screen.name = SCREEN_NAME;
	fractal->screen.x_offset = -SCREEN_WIDTH / 2;
	fractal->screen.y_offset = -SCREEN_HEIGHT / 2;
	fractal->screen.mouse_x = 0;
	fractal->screen.mouse_y = 0;
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

int	round_int(double d)
{
	int	rounded_value;

	rounded_value = (int)(d + 0.01);
	return (rounded_value);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	*dst;

	dst = data->addr + (y * data->line_length + \
				x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}