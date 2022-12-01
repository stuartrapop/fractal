/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:23:17 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/01 17:11:10 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <stdlib.h>
# include "mlx.h"
# include <stdio.h>
# include <math.h>

typedef struct s_world_point {
	double	x;
	double	y;
}	t_world_point;

typedef struct s_screen_point {
	int	x;
	int	y;
}	t_screen_point;

typedef struct s_data {
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_screen {
	int			width;
	int			height;
	char		*name;
	double		x_offset;
	double		y_offset;
	int			mouse_x;
	int			mouse_y;
	double		scale;
}	t_screen;

typedef struct s_fractal {
	void		*mlx;
	void		*mlx_win;
	t_screen	screen;
	t_data		img;
}	t_fractal;

# define SCREEN_WIDTH  800
# define SCREEN_HEIGHT  600
# define SCREEN_NAME  "Fractal Display"

void	initialize(t_fractal *fractal);
int		round_int(double d);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif