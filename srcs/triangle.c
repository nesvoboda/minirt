/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:42:55 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/17 18:59:43 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/triangle.h"

t_triangle	*new_triangle(t_v3 a, t_v3 b, t_v3 c)
{
	t_triangle *triangle;

	triangle = malloc(sizeof(t_triangle));
	triangle->a = a;
	triangle->b = b;
	triangle->c = c;
	return (triangle);
}

t_v3		get_triangle_normal(t_triangle triangle)
{
	t_v3	a;
	t_v3	b;
	t_v3	n;

	a = substract(triangle.b, triangle.a);
	b = substract(triangle.c, triangle.a);
	n = cross_product(a, b);
	normalize_vector(&n);
	return (n);
}

int			check_edges(t_triangle triangle, t_v3 p, t_v3 n)
{
	t_v3	c;
	t_v3	edge;
	t_v3	vp;

	edge = substract(triangle.b, triangle.a);
	vp = substract(p, triangle.a);
	c = cross_product(edge, vp);
	if (dot_product(n, c) < 0)
		return (0);
	edge = substract(triangle.c, triangle.b);
	vp = substract(p, triangle.b);
	c = cross_product(edge, vp);
	if (dot_product(n, c) < 0)
		return (0);
	edge = substract(triangle.a, triangle.c);
	vp = substract(p, triangle.c);
	c = cross_product(edge, vp);
	if (dot_product(n, c) < 0)
		return (0);
	return (1);
}

int			intersect_triangle(t_ray ray, t_triangle triangle, double *t)
{
	t_v3	a;
	t_v3	b;
	t_v3	n;
	double	angle;
	t_v3	p;

	a = substract(triangle.b, triangle.a);
	b = substract(triangle.c, triangle.a);
	n = cross_product(a, b);
	normalize_vector(&n);
	angle = dot_product(n, ray.direction);
	if (fabs(angle) < 1e-6)
		return (0);
	*t = (dot_product(n, substract(triangle.a, ray.origin)) / angle);
	if (*t < 0)
		return (0);
	p = v3_add(ray.origin, v3_multiply(ray.direction, *t));
	return (check_edges(triangle, p, n));
}
