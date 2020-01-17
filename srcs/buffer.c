/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:55:25 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/17 18:55:53 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"

t_pixel	**create_buffer(int height, int width)
{
	t_pixel	**result;
	int		i;

	i = 0;
	result = malloc(sizeof(t_pixel *) * height);
	while (i < height)
	{
		result[i] = malloc(sizeof(t_pixel) * width);
		i++;
	}
	return (result);
}

void	free_buffer(t_pixel **buffer, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}

t_pixel	pix_from_int(int color)
{
	t_color	tc;
	t_pixel	result;

	tc = int_to_color(color);
	result.b = tc.blue;
	result.g = tc.green;
	result.r = tc.red;
	return (result);
}
