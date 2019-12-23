/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 09:43:26 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 20:57:53 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

#include "v3.h"
#include "sphere.h"
#include "plane.h"
#include <math.h>
#include "quadratic.h"

typedef struct	s_cylinder
{
	t_v3 p;
	t_v3 normal;
	double radius;
	double height;
}				t_cylinder;

t_cylinder		*new_cylinder(t_v3 p, t_v3 normal, double radius,
														double height);
t_v3			get_cylinder_normal(t_v3 point, t_cylinder cylinder);
int				intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t);
void			check_t(double *t, t_cylinder cylinder, t_ray ray);
int				cyl_get_roots(double *t0, double *t1, t_cylinder cylinder,
																t_ray ray);
int				intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t);

#endif