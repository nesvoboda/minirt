/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:53:13 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 19:31:01 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

t_plane	*new_plane(t_v3 p0, t_v3 normal)
{
	t_plane *plane;

	plane = malloc(sizeof(t_plane));
	plane->p0 = p0;
	plane->normal = normal;
	return (plane);
}

t_v3	get_plane_normal(t_plane plane)
{
	t_v3 ret;

	ret = plane.normal;
	return (ret);
}

int		intersect_plane(t_ray ray, t_plane plane, double *t)
{
	double	denom;
	t_v3	p0l0;

	denom = dot_product(plane.normal, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		p0l0 = substract(plane.p0, ray.origin);
		*t = dot_product(p0l0, plane.normal) / denom;
		return (*t >= 0);
	}
	return (0);
}
