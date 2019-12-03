/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:47:57 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/03 17:24:21 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

union int_color
{
	int integer;
	unsigned char comps[4];
};

t_color int_to_color(int color)
{
	union int_color a;
	t_color result;

	a.integer = color;
	result.red = a.comps[2];
	result.green = a.comps[1];
	result.blue = a.comps[0];
	return (result);
}

int color_to_int(t_color color)
{
	union int_color a;

	a.comps[2] = color.red;
	a.comps[1] = color.green;
	a.comps[0] = color.blue;
	return (a.integer);
}

int	color_coefficient(int int_color, double coefficient)
{
	t_color comps;
	comps = int_to_color(int_color);
	comps.red = (int)(comps.red * coefficient) % 255;
	comps.green = (int)(comps.green * coefficient) % 255;
	comps.blue = (int)(comps.blue * coefficient) % 255;
	return (color_to_int(comps));
}