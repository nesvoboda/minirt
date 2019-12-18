/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 09:45:32 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/18 17:02:32 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

t_cylinder	*new_cylinder(t_v3 p, t_v3 normal, double radius, double height)
{
	t_cylinder *cylinder;
	cylinder = malloc(sizeof(t_cylinder));
	cylinder->p = p;
	cylinder->normal = normal;
	cylinder->radius = radius;
	cylinder->height = height;
	return (cylinder);
}

t_v3			get_cylinder_normal(t_v3 point, t_cylinder cylinder)
{
	t_v3 cent = v3_multiply(cylinder.normal, dot_product(cylinder.normal,
												substract(point, cylinder.p)));
	t_v3 normal = substract(cent, point);
	normalize_vector(&normal);
	return (normal);
}

int				intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t)
{
	t_v3 a_sqrt = substract(ray.direction,
								v3_multiply(cylinder.normal,
								dot_product(ray.direction, cylinder.normal)));
	double a = dot_product(a_sqrt, a_sqrt);

	t_v3 dp = substract(ray.origin, cylinder.p);
	t_v3 right = substract(dp,
						v3_multiply(cylinder.normal,
									dot_product(dp, cylinder.normal)));
	double b = 2 * dot_product(a_sqrt, right);

	double c = dot_product(right, right) - (cylinder.radius * cylinder.radius);

	double t0, t1;
	if (!solveQuadratic(a, b, c, &t0, &t1))
		return (0);

	if (t0 < 0) {
			t0 = t1; // if t0 is negative, let's use t1 instead
			if (t0 < 0)
				return (0); // both t0 and t1 are negative
	}
	*t = t0;

	t_v3 q = v3_add(ray.origin, v3_multiply(ray.direction, *t));

	t_v3 p2 = v3_add(cylinder.p, v3_multiply(cylinder.normal, cylinder.height));

	if (dot_product(cylinder.normal, substract(q, cylinder.p)) <= 0)
		return (0);

	if (dot_product(cylinder.normal, substract(q, p2)) >= 0)
		return (0);
	return (1);
}