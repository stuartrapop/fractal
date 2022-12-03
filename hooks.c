/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:36:32 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/03 10:05:13 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include "constants.h"

int	key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == ESCAPE)
		destroy_window(fractal);
	if (keycode == UPKEY)
		fractal->screen.y_offset += 50;
	if (keycode == DOWNKEY)
		fractal->screen.y_offset -= 50;
	if (keycode == RIGHTKEY)
		fractal->screen.x_offset -= 50;
	if (keycode == LEFTKEY)
		fractal->screen.x_offset += 50;
	if (keycode == PLUS)
		fractal->screen.scale += 0.2;
	if (keycode == MINUS)
		fractal->screen.scale -= 0.2;
	return (0);
}

void	update_offset(t_screen_point s_point, t_world_point w_point, \
	t_fractal *fractal)
{
	fractal->screen.x_offset = w_point.x - (double) s_point.x - \
			((double)s_point.x - (double)(fractal->screen.width / 2)) * \
			(1 - fractal->screen.scale);
	fractal->screen.y_offset = w_point.y -(double) s_point.y - \
			((double)s_point.y - (double)(fractal->screen.height / 2)) * \
			(1 - fractal->screen.scale);
}

int	mouse_down(int button, int x, int y, t_fractal *fractal)
{
	t_world_point	w_point1;
	t_world_point	w_point2;
	t_screen_point	s_point;

	s_point.x = x;
	s_point.y = y;
	screen_to_world(&s_point, &w_point1, fractal->screen);
	if (button == LEFTCLICK)
	{
		fractal->screen.mouse_down = 1;
		fractal->screen.pan_start_x = x;
		fractal->screen.pan_start_y = y;
	}
	if (button == SCROLL_IN)
	{
		fractal->screen.scale *= 1.1;
		screen_to_world(&s_point, &w_point2, fractal->screen);
		fractal->screen.x_offset -= (w_point2.x - w_point1.x);
		fractal->screen.y_offset -= (w_point2.y - w_point1.y);
	}
	if (button == SCROLL_OUT)
	{
		if (fractal->screen.scale < 0.3)
			return (0);
		fractal->screen.scale *= 0.9;
		screen_to_world(&s_point, &w_point2, fractal->screen);
		fractal->screen.x_offset -= (w_point2.x - w_point1.x);
		fractal->screen.y_offset -= (w_point2.y - w_point1.y);
	}

	printf("scale %f\n", fractal->screen.scale);
	return (0);
}

int	mouse_up(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == LEFTCLICK)
	{
		fractal->screen.mouse_down = 0;
	}
	return (0);
}

int	mouse_move(int x, int y, t_fractal *fractal)
{
	fractal->screen.mouse_x = x;
	fractal->screen.mouse_y = y;
	if (fractal->screen.mouse_down == 1)
	{
		if (x > 0 && y > 0 && \
			x < fractal->screen.width && y < fractal->screen.height)
		{
			fractal->screen.x_offset = fractal->screen.x_offset + \
				(fractal->screen.pan_start_x - x) / fractal->screen.scale;
			fractal->screen.y_offset = fractal->screen.y_offset + \
				(fractal->screen.pan_start_y - y) / fractal->screen.scale;
			fractal->screen.pan_start_x = x;
			fractal->screen.pan_start_y = y;
		}
	}
	return (0);
}
