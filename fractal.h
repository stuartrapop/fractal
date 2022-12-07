/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:23:17 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/07 10:37:16 by srapopor         ###   ########.fr       */
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
	int			pan_start_x;
	int			pan_start_y;
	int			mouse_x;
	int			mouse_y;
	int			mouse_down;
	double		scale;
}	t_screen;

typedef struct s_fractal {
	void		*mlx;
	void		*mlx_win;
	t_screen	screen;
	t_data		img;
	int			iter;
	double		z_x;
	double		z_y;
	double		cx;
	double		cy;
	char		kind[50];
}	t_fractal;

typedef struct s_rgb {
	int	r;
	int	g;
	int	b;
}	t_rgb;

void	initialize(t_fractal *fractal);
int		destroy_window(t_fractal *fractal);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_hook(int keycode, t_fractal *fractal);
void	update_offset(t_screen_point s_point, t_world_point w_point,
			t_fractal *fractal);
int		mouse_down(int button, int x, int y, t_fractal *fractal);
int		mouse_up(int button, int x, int y, t_fractal *fractal);
int		mouse_move(int x, int y, t_fractal *fractal);
void	screen_to_world(t_screen_point *s_point, t_world_point *w_point,
			t_screen screen);
void	world_to_screen(t_screen_point *s_point, t_world_point *w_point,
			t_screen screen);
int		get_fractal_color(int iteration, int max_iterations);
int		destroy_window(t_fractal *fractal);

#endif