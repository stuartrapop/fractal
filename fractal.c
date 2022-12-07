/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:44:06 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/07 14:29:31 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include "constants.h"

int	mandelbrot(t_world_point w_point, t_fractal *fra)
{
	double	temp;

	fra->iter = 1;
	fra->cx = (w_point.x) / fra->screen.width * 5;
	fra->cy = (w_point.y) / fra->screen.height * 5;
	fra->z_x = 0;
	fra->z_y = 0;
	if (w_point.x < -fra->screen.width / 2 || w_point.x > \
		fra->screen.width / 2 || w_point.y < -fra->screen.height / 2 \
		|| w_point.y > fra->screen.height / 2)
		return (0x000000);
	while ((fra->z_x * fra->z_x + fra->z_y * fra-> z_y) < 4 && \
		fra->iter <= MAX_ITER)
	{
		temp = fra->z_x * fra->z_x - fra-> z_y * fra->z_y + fra->cx;
		fra->z_y = 2 * fra->z_x * fra->z_y + fra->cy;
		fra->z_x = temp;
		fra->iter++;
	}
	if ((fra->z_x * fra->z_x + fra-> z_y * fra->z_y) < 4)
		return (0xFF0000);
	else
		return (get_fractal_color(fra->iter, MAX_ITER, fra));
}

int	julia(t_world_point w_point, t_fractal *fra)
{
	double	temp;
	double	r;

	fra->iter = 1;
	fra->cx = -0.7269;
	fra->cy = 0.1889;
	r = 4;
	fra->z_x = (w_point.x) / fra->screen.width * 5;
	fra->z_y = (w_point.y) / fra->screen.height * 5;
	if (w_point.x < -fra->screen.width / 2 || w_point.x > \
		fra->screen.width / 2 || w_point.y < -fra->screen.height / 2 \
		|| w_point.y > fra->screen.height / 2)
		return (0x000000);
	while ((fra->z_x * fra->z_x + fra->z_y * fra-> z_y) < r && \
		fra->iter <= MAX_ITER)
	{
		temp = fra->z_x * fra->z_x - fra-> z_y * fra->z_y;
		fra->z_y = 2 * fra->z_x * fra->z_y + fra->cy;
		fra->z_x = temp + fra->cx;
		fra->iter++;
	}
	if ((fra->z_x * fra->z_x + fra-> z_y * fra->z_y) < r)
		return (0xFF0000);
	else
		return (get_fractal_color(fra->iter, MAX_ITER, fra));
}

int	burningship(t_world_point w_point, t_fractal *fra)
{
	double	temp;

	fra->iter = 1;
	fra->cx = (w_point.x) / fra->screen.width * 5;
	fra->cy = (w_point.y) / fra->screen.height * 5;
	fra->z_x = 0;
	fra->z_y = 0;
	if (w_point.x < -fra->screen.width / 2 || w_point.x > \
		fra->screen.width / 2 || w_point.y < -fra->screen.height / 2 \
		|| w_point.y > fra->screen.height / 2)
		return (0x000000);
	while ((fra->z_x * fra->z_x + fra->z_y * fra-> z_y) < 4 && \
		fra->iter <= MAX_ITER)
	{
		temp = (fra->z_x * fra->z_x - fra-> z_y * fra->z_y + fra->cx);
		fra->z_y = fabs(2 * fra->z_x * fra->z_y) + fra->cy;
		fra->z_x = temp;
		fra->iter++;
	}
	if ((fra->z_x * fra->z_x + fra-> z_y * fra->z_y) < 4)
		return (0xFF0000);
	else
		return (get_fractal_color(fra->iter, MAX_ITER, fra));
}
