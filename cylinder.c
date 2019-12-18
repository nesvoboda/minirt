/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 09:45:32 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/18 13:50:12 by ashishae         ###   ########.fr       */
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
	t_v3 normal = substract(point, cent);
	normalize_vector(&normal);
	return (normal);
}

int				intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t)
{
	t_v3 a_sqrt = substract(ray.direction,
								v3_multiply(cylinder.normal,
								dot_product(ray.direction, cylinder.normal)));
	double a = dot_product(a_sqrt, a_sqrt);

	t_v3 left = substract(ray.direction,
							v3_multiply(cylinder.normal,
							dot_product(ray.direction, cylinder.normal)));
	t_v3 dp = substract(ray.origin, cylinder.p);
	t_v3 right = substract(dp,
						v3_multiply(cylinder.normal,
									dot_product(dp, cylinder.normal)));
	double b = 2 * dot_product(a_sqrt, right);

	double c = dot_product(right, right) - (cylinder.radius * cylinder.radius)
}