/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:44:06 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/07 14:50:28 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include "constants.h"
#include <unistd.h>

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
			color = fractal->fun_ptr(w_point, fractal);
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

void	display_options(void)
{
	ft_putstr("\n\nRun program with one of the following options:\n");
	ft_putstr("./fractol Mandelbrot\n");
	ft_putstr("./fractol Julia\n");
	ft_putstr("./fractol BurningShip\n");
	exit(0);
}

void	choose_fractal(int argc, char *argv[], t_fractal *fractal)
{
	(void)argv;
	if (argc != 2)
		display_options();
	if (ft_strcmp(argv[1], "Mandelbrot") == 0)
		fractal->fun_ptr = &mandelbrot;
	else if (ft_strcmp(argv[1], "Julia") == 0)
	{
		fractal->fun_ptr = &julia;
	}
	else if (ft_strcmp(argv[1], "BurningShip") == 0)
		fractal->fun_ptr = &burningship;
	else
		display_options();
}

int	main(int argc, char *argv[])
{
	t_fractal	fractal;

	choose_fractal(argc, argv, &fractal);
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
