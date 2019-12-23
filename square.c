/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:10:46 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 19:10:38 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"
#include "math.h"

t_square	*new_square(t_v3 center, t_v3 normal, double length)
{
	t_square *square;

	square = malloc(sizeof(t_square));
	square->center = center;
	square->normal = normal;
	square->length = length;
	return (square);
}

t_v3		get_square_normal(t_square square)
{
	t_v3 ret;

	ret = square.normal;
	return (ret);
}

int			intersect_square(t_ray ray, t_square square, double *t)
{
	double	denom;
	t_v3	hit_point;
	t_v3	p0l0;

	denom = dot_product(square.normal, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		p0l0 = substract(square.center, ray.origin);
		*t = dot_product(p0l0, square.normal) / denom;
		hit_point = v3_add(ray.origin, v3_multiply(ray.direction, *t));
		if (*t >= 0)
		{
			if (fabs(hit_point.x - square.center.x) > (square.length / 2))
				return (0);
			if (fabs(hit_point.y - square.center.y) > (square.length / 2))
				return (0);
			if (fabs(hit_point.z - square.center.z) > (square.length / 2))
				return (0);
			else
				return (1);
		}
		else
			return (0);
	}
	return (0);
}
