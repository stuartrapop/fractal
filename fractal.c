/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:44:06 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/04 16:15:57 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include "constants.h"

int	mandelbrot(t_world_point w_point, t_fractal *fra)
{
	double	temp;

	fra->iter = 1;
	fra->cx = (w_point.x)/ fra->screen.width * 5 ;
	fra->cy = (w_point.y) / fra->screen.height * 5;
	fra->z_x = 0;
	fra->z_y = 0;

	if (w_point.x < -fra->screen.width / 2 || w_point.x > \
		fra->screen.width / 2 || w_point.y < -fra->screen.height / 2 \
		|| w_point.y > fra->screen.height / 2)
		return (0x000000);
	while ((fra->z_x * fra->z_x + fra->z_y * fra-> z_y) < 4 && fra->iter <= 400)
	{
		temp = fra->z_x * fra->z_x - fra-> z_y * fra->z_y + fra->cx;
		fra->z_y = 2 * fra->z_x * fra->z_y + fra->cy;
		fra->z_x = temp;
		fra->iter++;
	}
	if ((fra->z_x * fra->z_x + fra-> z_y * fra->z_y) < 4)
		return (0xFF0000);
	else
		return (get_fractal_color(fra->iter, 400));
}

int	julia(t_world_point w_point, t_fractal *fra)
{
	double	temp;

	fra->iter = 1;
	fra->cx = 1;
	fra->cy = 0;
	fra->z_x = (w_point.x )/ fra->screen.width * 5 ;
	fra->z_y = (w_point.y ) / fra->screen.height * 5;

	if (w_point.x < -fra->screen.width / 2 || w_point.x > \
		fra->screen.width / 2 || w_point.y < -fra->screen.height / 2 \
		|| w_point.y > fra->screen.height / 2)
		return (0x000000);
	while ((fra->z_x * fra->z_x + fra->z_y * fra-> z_y) < 4 && fra->iter <= 400)
	{
		temp = fra->z_x * fra->z_x - fra-> z_y * fra->z_y + fra->cx;
		fra->z_y = 2 * fra->z_x * fra->z_y + fra->cy;
		fra->z_x = temp;
		fra->iter++;
	}
	if ((fra->z_x * fra->z_x + fra-> z_y * fra->z_y) < 4)
		return (0xFF0000);
	else
		return (get_fractal_color(fra->iter, 400));
}



int	experiment(t_world_point w_point, t_fractal *fra)
{
	double	temp;

	fra->iter = 1;
	fra->cx =0;
	fra->cy = 0;
	fra->z_x = (w_point.x )/ fra->screen.width * 5 ;
	fra->z_y = (w_point.y ) / fra->screen.height * 5;

	if (w_point.x < -fra->screen.width / 2 || w_point.x > \
		fra->screen.width / 2 || w_point.y < -fra->screen.height / 2 \
		|| w_point.y > fra->screen.height / 2)
		return (0x000000);
	while ((fra->z_x * fra->z_x + fra->z_y * fra-> z_y) < 4 && fra->iter <= 400)
	{
		temp = (fra->z_x * fra->z_x - fra-> z_y * fra->z_y + fra->cx) * (1 -0.005) - 1 ;
		fra->z_y =( 2 * fra->z_x * fra->z_y + fra->cy) * (1 -0.005) ;
		fra->z_x = temp;
		fra->iter++;
	}
	if ((fra->z_x * fra->z_x + fra-> z_y * fra->z_y) < 4)
		return (0xFF0000);
	else
		return (get_fractal_color(fra->iter, 400));
}

int	get_square(t_world_point w_point, int color)
{
	if ((w_point.x < 100) && (w_point.y < 100) && \
		(w_point.x > -100) && (w_point.y > -100))
		return (color);
	else
		return (0xFFFFFF);
}

void	my_mlx_draw_screen(t_fractal *fractal)
{
	t_screen_point	s_point;
	t_world_point	w_point;
	int				color;

	s_point.x = 0;
	while (s_point.x < fractal->screen.width)
	{
		s_point.y = 0;
		while (s_point.y < fractal->screen.height)
		{
			screen_to_world(&s_point, &w_point, fractal->screen);
			// color = mandelbrot(w_point, fractal);
			// color = julia(w_point, fractal);
			color = experiment(w_point, fractal);
			my_mlx_pixel_put(&(fractal->img), s_point.x, s_point.y, color);
			s_point.y++;
		}
		s_point.x++;
	}
}

int	render(t_fractal *fractal)
{
	my_mlx_draw_screen(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->mlx_win, \
		fractal->img.img, 0, 0);
	return (1);
}

int	destroy_window(t_fractal *fractal)
{
	fractal->screen.width = 800;
	mlx_destroy_image(fractal->mlx, fractal->img.img);
	mlx_destroy_window(fractal->mlx, fractal->mlx_win);


	exit(0);
}

int	main(void)
{
	t_fractal	fractal;

	get_fractal_color(1750, 3000);
	initialize(&fractal);
	mlx_loop_hook(fractal.mlx, &render, &fractal);
	mlx_hook(fractal.mlx_win, ON_MOUSEDOWN, 0, &mouse_down, &fractal);
	mlx_hook(fractal.mlx_win, ON_MOUSEUP, 0, &mouse_up, &fractal);
	mlx_hook(fractal.mlx_win, ON_MOUSEMOVE, 0, &mouse_move, &fractal);
	mlx_hook(fractal.mlx_win, 17, 0, &destroy_window, &fractal);
	mlx_key_hook (fractal.mlx_win, &key_hook, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
