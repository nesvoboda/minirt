/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:50:13 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/17 13:54:24 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "v3.h"
# include "ray.h"

typedef struct	s_sphere
{
	t_v3 center;
	double radius;
}				t_sphere;
t_sphere		*new_sphere(t_v3 center, double radius);
t_v3			get_sphere_normal(t_v3 point, t_sphere sphere);
void			swap_doubles(double *a, double *b);
int				solveQuadratic(double a, double b, double c, double *x0,
								double *x1);
int				intersect_sphere(t_ray ray, t_sphere sphere, double *t);

#endif