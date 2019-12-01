/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:25:35 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/01 09:45:16 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	create_ray(t_v3 origin, t_v3 direction)
{
	t_ray result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}
