/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:42:01 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/17 13:53:55 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_H
# define SHADING_H

#include "minirt.h"

t_v3	get_normal(t_v3 point, t_object *object);
double	light_contribution(t_light light, t_v3 hit_point, t_v3 hit_normal, t_list *objects, t_object *closest_object);
double	shade(t_list *objects, t_list *lights, t_ray sent, t_object *closest_object, double t_min);
int		get_color(t_list *objects, t_list *lights, t_ray sent);

#endif