/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:48:36 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/17 12:51:45 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

t_sphere 	*new_sphere(t_v3 center, double radius)
{
	t_sphere *sphere;
	sphere = malloc(sizeof(t_sphere));
	sphere->center = center;
	sphere->radius = radius;
	return (sphere);
}

t_v3	get_sphere_normal(t_v3 point, t_sphere sphere)
{
	t_v3 n = substract(point, sphere.center);
	normalize_vector(&n);
	return (n);
}

void	swap_doubles(double *a, double *b)
{
	double buffer;
	buffer = *a;
	*a = *b;
	*b = buffer;
}

int solveQuadratic(double a, double b, double c, double *x0, double *x1)
{
    double discr = b * b - 4.0 * a * c;
    if (discr < 0)
    	return (0);
    else if (discr == 0)
    {
    	*x0 = *x1 = -0.5 * b / a;
    }
    else
    {
        double q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
        *x0 = q / a;
        *x1 = c / q;
    }
	if (*x0 > *x1)
		swap_doubles(x0, x1);

    return (1);
}

int	intersect_sphere(t_ray ray, t_sphere sphere, double *t)
{
		double t0;
		double t1;

		t_v3 l = substract(ray.origin, sphere.center);
		double a = dot_product(ray.direction, ray.direction);
		double b = 2.0 * dot_product(ray.direction, l);
		double c = dot_product(l, l) - (sphere.radius * sphere.radius);
		if (!solveQuadratic(a, b, c, &t0, &t1))
			return 0;

		if (t0 < 0) {
			t0 = t1; // if t0 is negative, let's use t1 instead
			if (t0 < 0)
				return (0); // both t0 and t1 are negative
		}
		*t = t0;
		return (1);
}