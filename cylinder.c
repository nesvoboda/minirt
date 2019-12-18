/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 09:45:32 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/18 19:27:36 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include "plane.h"
#include <math.h>

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
	t_v3 ctp = substract(point, cylinder.p);
	t_v3 normal = substract(ctp,
						v3_multiply(cylinder.normal, dot_product(cylinder.normal, ctp)));



	// t_v3 cent = v3_multiply(cylinder.normal, dot_product(cylinder.normal,
	// 											substract(cylinder.p, point)));
	// t_v3 normal = substract(cent, point);
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

	t_v3 q;

	t_v3 p2 = v3_add(cylinder.p, v3_multiply(cylinder.normal, cylinder.height));

	if (t0 > 0)
	{
		q = v3_add(ray.origin, v3_multiply(ray.direction, t0));

		if (dot_product(cylinder.normal, substract(q, cylinder.p)) <= 0)
			t0 = -1;

		if (dot_product(cylinder.normal, substract(q, p2)) >= 0)
			t0 = -1;
	}

	if (t1 > 0)
	{
		q = v3_add(ray.origin, v3_multiply(ray.direction, t1));

		if (dot_product(cylinder.normal, substract(q, cylinder.p)) <= 0)
			t1 = -1;

		if (dot_product(cylinder.normal, substract(q, p2)) >= 0)
			t1 = -1;
	}

	if (t0 < 0 && t1 < 0)
		return (0);

	if (t1 < t0)
		if (t1 > 0)
			*t = t1;
		else
			*t = t0;
	else
		if (t0 > 0)
			*t = t0;
		else
			*t = t1;

	// double t3;
	// double t4;

	// t_v3 v;
	// t_plane *bottom_plane = new_plane(cylinder.p, cylinder.normal);
	// t_plane *top_plane = new_plane(p2, cylinder.normal);
	// if (intersect_plane(ray, *bottom_plane, &t3))
	// {
	// 	q = v3_add(ray.origin, v3_multiply(ray.direction, t3));
	// 	v = substract(q, cylinder.p);
	// 	if (sqrt(dot_product(v, v)) >= cylinder.radius)
	// 		t3 = -1;
	// }
	// if (intersect_plane(ray, *top_plane, &t4))
	// {
	// 	q = v3_add(ray.origin, v3_multiply(ray.direction, t4));
	// 	v = substract(q, p2);
	// 	if (sqrt(dot_product(v, v)) >= cylinder.radius)
	// 		t4 = -1;
	// }
	// if (t4 < t3)
	// 	swap_doubles(&t3, &t4);

	// if (t3 < 0) {
	// 		t3 = t4; // if t0 is negative, let's use t1 instead
	// }
	// if (t0 < 0 && t3 < 0)
	// 	return (0);
	// else if (t3 < 0 || t0 < t3)
	// 	*t = t0;
	// else
	// 	*t = t3;

	return (1);
}