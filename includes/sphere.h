/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:50:13 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 21:01:36 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "v3.h"
# include "ray.h"
# include "quadratic.h"

typedef struct	s_sphere
{
	t_v3	center;
	double	radius;
}				t_sphere;

t_sphere		*new_sphere(t_v3 center, double radius);
t_v3			get_sphere_normal(t_v3 point, t_sphere sphere);
int				intersect_sphere(t_ray ray, t_sphere sphere, double *t);
int				get_roots(double *t0, double *t1, t_ray ray, t_sphere sphere);

#endif
