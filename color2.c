/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 10:57:02 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 16:41:06 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color2.h"

t_color2 int_color(int color)
{
	t_color this;
	t_color2 result;


	this = int_to_color(color);


	result.red = (float)this.red / 256;
	result.green = (float)this.green / 256;
	result.blue = (float)this.blue / 256;

	return (result);
}

t_color2 from_color(t_color a)
{
	t_color2 result;
	result.red = a.red / 256;
	result.green = a.green / 256;
	result.blue = a.blue / 256;
	return (result);
}

t_color2 from_rgb(int r, int g, int b)
{
	t_color2 result;
	result.red = (float)r / 256;
	result.green = (float)g / 256;
	result.blue = (float)b / 256;
	return (result);
}

t_color2 color2_add(t_color2 a, t_color2 b)
{
	t_color2 result;

	result.red = fmin(a.red + b.red, 1);
	result.green = fmin(a.green + b.green, 1);
	result.blue = fmin(a.blue + b.blue, 1);
	return(result);
}

t_color2 color2_mult(t_color2 a, t_color2 b)
{
	t_color2 result;

	result.red = fmin(a.red * b.red, 1);
	result.green = fmin(a.green * b.green, 1);
	result.blue = fmin(a.blue * b.blue, 1);
	return(result);
}

t_color2 color2_coeff(t_color2 a, double coeff)
{
	t_color2 result;

	result.red = fmin(a.red * coeff, 1);
	result.green = fmin(a.green * coeff, 1);
	result.blue = fmin(a.blue * coeff, 1);
	return(result);
}

int to_int(t_color2 a)
{
	int result;
	t_color this;

	this.red = a.red * 256;
	this.green = a.green * 256;
	this.blue = a.blue * 256;
	result = color_to_int(this);
	return (result);
}