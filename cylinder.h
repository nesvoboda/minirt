/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 09:43:26 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/18 10:02:58 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v3.h"
#include "sphere.h"

typedef struct	s_cylinder
{
	t_v3 p;
	t_v3 normal;
	double radius;
	double height;
}				t_cylinder;

t_cylinder		*new_cylinder(t_v3 p, t_v3 normal, double radius, double height);
t_v3			get_cylinder_normal(t_v3 point, t_cylinder cylinder);
int				intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t);