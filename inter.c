/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 20:31:01 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 20:31:12 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shading.h"

t_inter		new_inter(t_v3 hit_point, t_v3 hit_normal, t_list *objects,
													t_object *closest_object)
{
	t_inter inter;

	inter.hit_point = hit_point;
	inter.hit_normal = hit_normal;
	inter.objects = objects;
	inter.closest_object = closest_object;

	return (inter);
}
