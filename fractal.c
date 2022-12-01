/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:44:06 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/01 18:01:05 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include "keycode.h"

int	get_square(t_world_point w_point, int color)
{
	if ((w_point.x < 200) && (w_point.y < 200) && \
		(w_point.x > 0) && (w_point.y > 0))
		return (color);
	else
		return (0xFFFFFF);
}

void	screen_to_world(t_screen_point *s_point, t_world_point *w_point, \
	t_screen screen)
{
	int	x;
	int	y;

	x = s_point->x + (s_point->x - screen.width / 2) * (1 - screen.scale);
	y = s_point->y + (s_point->y - screen.height / 2) * (1 - screen.scale);
	w_point->x = (double)(x + screen.x_offset);
	w_point->y = (double)(y + screen.y_offset);
}

void	world_to_screen(t_screen_point *s_point, t_world_point *w_point, \
	t_screen screen)
{
	s_point->x = (int)(w_point->x - screen.x_offset);
	s_point->y = (int)(w_point->y - screen.y_offset);
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
			color = get_square(w_point, 0xFF0000);
			my_mlx_pixel_put(data, s_point.x, s_point.y, color);
			s_point.y++;
		}
		s_point.x++;
	}
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == ESCAPE)
		printf("upkey pressed\n");
	if (keycode == UPKEY)
		fractal->screen.y_offset += 50;
	if (keycode == DOWNKEY)
		fractal->screen.y_offset -= 50;
	if (keycode == RIGHTKEY)
		fractal->screen.x_offset -= 50;
	if (keycode == LEFTKEY)
		fractal->screen.x_offset += 50;
	if (keycode == PLUS)
		fractal->screen.scale *= 1.1;
	if (keycode == MINUS)
		fractal->screen.scale *= 0.9;
	
	printf("key pressed %d\n", keycode);
	printf("scale %f\n", fractal->screen.scale);
	printf("offset %f %f\n", fractal->screen.x_offset, fractal->screen.y_offset);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractal *fractal)
{
	if (button == LEFTCLICK || button == SCROLL_IN)
	{
		fractal->screen.scale *= 1.1;
		fractal->screen.x_offset = fractal->screen.x_offset - ( fractal->screen.width / 2 - x) * (0.9 - 1);
		fractal->screen.y_offset = fractal->screen.y_offset - ( fractal->screen.height / 2 - y) * (0.9 - 1);

	}
	if (button == RIGHTCLICK || button == SCROLL_OUT)
	{
		fractal->screen.scale *= 0.9;
		fractal->screen.x_offset = fractal->screen.x_offset - ( fractal->screen.width / 2 - x) * (1.1 - 1);
		fractal->screen.y_offset = fractal->screen.y_offset - ( fractal->screen.height / 2 - y) * (1.1 - 1);
	}
	fractal->screen.mouse_x = x;
	fractal->screen.mouse_y = y;
	printf("mouse pressed %d %d  %d %f\n", button, x, y, fractal->screen.x_offset);
	return (0);
}

int	render(t_fractal *fractal)
{
	my_mlx_draw_screen(&(fractal->img), (fractal->screen));
	mlx_put_image_to_window(fractal->mlx, fractal->mlx_win, \
		fractal->img.img, 0, 0);
	return (1);
}

int	main(void)
{
	t_fractal	fractal;

	initialize(&fractal);
	mlx_loop_hook(fractal.mlx, &render, &fractal);
	mlx_key_hook (fractal.mlx_win, &key_hook, &fractal);
	mlx_mouse_hook (fractal.mlx_win, &mouse_hook, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
