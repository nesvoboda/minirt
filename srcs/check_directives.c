/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:04:10 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/17 18:56:01 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int		check_color2(t_color2 c)
{
	if (c.red < 0 || c.red > 1 || c.green < 0 || c.green > 1 || c.blue < 0 ||
	c.blue > 1)
		return (0);
	return (1);
}

void	parse_color2(t_color2 *result, char *field, char *errmsg)
{
	char **color;

	color = ft_split(field, ',');
	if (line_fields(color) != 3)
		handle_error(errmsg);
	result->red = (double)ft_atoi(color[0]) / 256;
	result->green = (double)ft_atoi(color[1]) / 256;
	result->blue = (double)ft_atoi(color[2]) / 256;
}

void	parse_coords(t_v3 *point, char *field, char *errmsg)
{
	char **coords;

	coords = ft_split(field, ',');
	if (line_fields(coords) != 3)
		handle_error(errmsg);
	point->x = ft_atod(coords[0]);
	point->y = ft_atod(coords[1]);
	point->z = ft_atod(coords[2]);
}

int		check_normal(t_v3 n)
{
	if (n.x < -1 || n.x > 1 || n.y < -1 || n.y > 1 || n.z < -1 || n.z > 1)
		return (0);
	return (1);
}
