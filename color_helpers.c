/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapopor <srapopor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:44:48 by srapopor          #+#    #+#             */
/*   Updated: 2022/11/23 17:03:32 by srapopor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <math.h>


#include <mlx.h>

void	dec_to_hex(int n, char *pair)
{
	char	*hex;
	int		remainder;

	if (n < 0 || n > 255)
		return ;

	if (n % 16 > 9)
		pair[1] = n % 16 + 'A';
	else
		pair[1] = n % 16 + '0';
	n = n / 16;
	if (n % 16 > 9)
		pair[0] = n % 16 + 'A';
	else
		pair[0] = n % 16 + '0';
}

void	ft_rgb_to_hex(int r, int g, int b, char *hex)
{
	hex[0] = '#';
	dec_to_hex(r, &hex[1]);
	dec_to_hex(g, &hex[3]);
	dec_to_hex(b, &hex[5]);
}