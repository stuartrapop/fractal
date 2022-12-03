/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:44:06 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/03 19:21:29 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include "constants.h"

int	fractal_put(t_world_point w_point, t_screen screen)
{
	int		iterations;
	double	z_x;
	double	z_y;
	double	cx;
	double	cy;
	double	temp;

	iterations = 1;
	cx = w_point.x / screen.width * 5 - 0.12375;
	cy = w_point.y / screen.height * 5 + 0.56508;
	z_x = 0;
	z_y = 0;

	if (w_point.x < -screen.width / 2 || w_point.x > screen.width / 2 || \
		w_point.y < -screen.height / 2 || w_point.y > screen.height / 2)
		return (0x000000);
	while ((z_x * z_x + z_y * z_y) < 4 && iterations <= 400)
	{
		temp = z_x * z_x - z_y * z_y + cx;
		z_y = -2 * z_x * z_y + cy;
		z_x = temp;
		iterations++;
	}
	if ((z_x * z_x + z_y * z_y) < 4)
		return (0xFF0000);
	else
		return (get_fractal_color(iterations, 400));
}

int	get_square(t_world_point w_point, int color)
{
	if ((w_point.x < 100) && (w_point.y < 100) && \
		(w_point.x > -100) && (w_point.y > -100))
		return (color);
	else
		return (0xFFFFFF);
}

void	my_mlx_draw_screen(t_data *data, t_screen screen)
{
	t_screen_point	s_point;
	t_world_point	w_point;
	int				color;

	s_point.x = 0;
	while (s_point.x < screen.width)
	{
		s_point.y = 0;
		while (s_point.y < screen.height)
		{
			screen_to_world(&s_point, &w_point, screen);
			// color = get_square(w_point, 0xFF0000);
			color = fractal_put(w_point, screen);
			my_mlx_pixel_put(data, s_point.x, s_point.y, color);
			s_point.y++;
		}
		s_point.x++;
	}
}

int	render(t_fractal *fractal)
{
	my_mlx_draw_screen(&(fractal->img), (fractal->screen));
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
