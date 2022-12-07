/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:44:48 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/07 14:50:55 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractal.h"
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <unistd.h>

void	int_to_rgb(int color, t_rgb *rgb)
{
	rgb->b = color % 256;
	color /= 256;
	rgb->g = color % 256;
	color /= 256;
	rgb->r = color % 256;
}

int	get_fractal_color(int iteration, int max_iterations, t_fractal *fractal)
{
	t_rgb	s;

	if (iteration == max_iterations)
		return (0x00000);
	if (fractal->color_shift)
	{
	s.r = 0;
	s.g = (int)(sin(0.3 * (double)iteration + 3) * 127) + (int)128;
	s.b = 0;
	}
	else
	{
	s.r = 0;
	s.g = (int)(sin(0.3 * (double)iteration + 3) * 127) + (int)128;
	s.b = (int)(sin(0.3 * (double)iteration + 3) * 127) + (int)128;
	}
	return (s.r << 16 | s.g << 8 | s.b);
}

void	shift_colors(t_fractal *fractal)
{
	if (fractal->color_shift == 0)
		fractal->color_shift = 1;
	else if (fractal->color_shift == 1)
		fractal->color_shift = 0;
}
