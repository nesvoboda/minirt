/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:54:27 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/17 13:53:30 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "v3.h"
# include "ray.h"

typedef struct s_plane
{
	t_v3 p0;
	t_v3 normal;
}				t_plane;

t_plane			*new_plane(t_v3 p0, t_v3 normal);
t_v3			get_plane_normal(t_plane plane);
int				intersect_plane(t_ray ray, t_plane plane, double *t);

#endif