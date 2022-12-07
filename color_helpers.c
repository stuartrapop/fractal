/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:44:48 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/07 10:23:11 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractal.h"
#include <stdio.h>
#include <math.h>
#include <mlx.h>

void	int_to_rgb(int color, t_rgb *rgb)
{
	rgb->b = color % 256;
	color /= 256;
	rgb->g = color % 256;
	color /= 256;
	rgb->r = color % 256;
}

int	get_fractal_color(int iteration, int max_iterations)
{
	t_rgb	s;

	if (iteration == max_iterations)
		return (0x00000);
	s.r = sin(0.3 * (double)iteration);
	s.g = sin(0.3 * (double)iteration + 3) * 127 + 128;
	s.b = sin(0.3 * (double)iteration + 3) * 127 + 128;
	return (s.r << 16 | s.g << 8 | s.b);
}
