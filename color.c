/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:47:57 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/21 19:41:24 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "math.h"

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

int color_to_int2(t_color color)
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
	comps.red = (int)(comps.red * coefficient);
	comps.green = (int)(comps.green * coefficient);
	comps.blue = (int)(comps.blue * coefficient);
	return (color_to_int(comps));
}

int	color_add(int int_color, double add)
{
	t_color comps;
	comps = int_to_color(int_color);
	comps.red = (int)(comps.red + add);
	comps.green = (int)(comps.green + add);
	comps.blue = (int)(comps.blue + add);
	return (color_to_int(comps));
}

int color_concat(int c1, int c2)
{
	t_color comps1;
	t_color comps2;
	t_color result;
	comps1 = int_to_color(c1);
	comps2 = int_to_color(c2);
	result.red = comps1.red + comps2.red;
	result.green = comps1.green + comps2.green;
	result.blue = comps1.blue + comps2.blue;
	return (color_to_int(result));
}

// int color_mult(int c1, int c2)
// {
// 	t_color comps1;
// 	t_color comps2;
// 	t_color result;
// 	comps1 = int_to_color(c1);
// 	comps2 = int_to_color(c2);
// 	result.red = (int)(((float)(comps1.red / 255) * (float)(comps2.red / 255) * 255);
// 	result.green = (int)(((float)(comps1.green) / 255) * (float)(comps2.green) / 255)) * 255);
// 	result.blue = (int)(((float)(comps1.blue) / 255) * (float)(comps2.blue) / 255)) * 255);
// 	return (color_to_int(result));
// }