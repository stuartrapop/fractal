/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:26:15 by srapopor          #+#    #+#             */
/*   Updated: 2022/12/07 14:57:34 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define UPKEY  126
# define DOWNKEY  125
# define RIGHTKEY  124
# define LEFTKEY  123
# define ESCAPE 53
# define PLUS 24
# define MINUS 27

# define LEFTCLICK 1
# define RIGHTCLICK 2
# define SCROLL_IN 5
# define SCROLL_OUT 4

typedef enum e_events {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}	t_events;

# define SCREEN_WIDTH  800
# define SCREEN_HEIGHT  600
# define SCREEN_NAME  "Fractal Display"
# define MAX_ITER 200

#endif