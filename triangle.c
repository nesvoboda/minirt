/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:42:55 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/17 15:49:09 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

t_triangle		*new_triangle(t_v3 a, t_v3 b, t_v3 c)
{
	t_triangle *triangle;
	triangle = malloc(sizeof(t_triangle));
	triangle->a = a;
	triangle->b = b;
	triangle->c = c;
	return (triangle);
}

//t_v3	get_triangle_normal(t_triangle triangle, t_ray ray)
t_v3	get_triangle_normal(t_triangle triangle)
{
	t_v3 A = substract(triangle.b, triangle.a);
	t_v3 B = substract(triangle.c, triangle.a);
	t_v3 N = cross_product(A, B);
	normalize_vector(&N);
	//if (dot(N, ray.direction) < 0.0)
	//N = substract(create_v3(0, 0, 0), N);
	//printf("N: %f %f %f\n", N.x, N.y, N.z);
	return (N);
}

int intersect_triangle(t_ray ray, t_triangle triangle, double *t)
{
	t_v3 A = substract(triangle.b, triangle.a);
	t_v3 B = substract(triangle.c, triangle.a);
	t_v3 N = cross_product(A, B);
	normalize_vector(&N);
	//double sign = -1;

	double angle = dot_product(N, ray.direction);
	if (fabs(angle) < 1e-6)
	{

		return (0);
	}

	//double d = dot_product(N, triangle.a);

	*t = (dot_product(N, substract(triangle.a, ray.origin)) / angle);

	if (*t < 0)
	{
		return (0);
	}
	t_v3 p = v3_add(ray.origin, v3_multiply(ray.direction, *t));

	t_v3 C;

	t_v3 edge0 = substract(triangle.b, triangle.a);
	t_v3 vp0 = substract(p, triangle.a);

	C = cross_product(edge0, vp0);

	if (dot_product(N, C) < 0)
		return (0);

	t_v3 edge1 = substract(triangle.c, triangle.b);
	t_v3 vp1 = substract(p, triangle.b);
	C = cross_product(edge1, vp1);

	if (dot_product(N, C) < 0)
		return (0);

	t_v3 edge2 = substract(triangle.a, triangle.c);
	t_v3 vp2 = substract(p, triangle.c);

	C = cross_product(edge2, vp2);

	if (dot_product(N, C) < 0)
		return (0);

	return (1);
}
