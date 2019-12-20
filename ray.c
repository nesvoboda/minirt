/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:25:35 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 15:45:33 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt.h"
#include "matrix.h"


t_ray	create_ray(t_v3 origin, t_v3 direction)
{
	t_ray result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

t_ray	ray_to_pixel(int x, int y, t_scene *scene)
{
	double aspect_ratio;
	double p_x;
	double p_y;
	t_v3 	origin;
	t_v3	direction;
	t_matrix c2w;

	t_v3 forward = create_v3(0, 0, 1);
	normalize_vector(&forward);

	c2w = lookAt(scene->camera.origin, scene->camera.direction);
	double fov_coeff =tan((double)scene->camera.fov / 2 * M_PI / 180);
	aspect_ratio = (double)scene->width / (double)scene->height;
	p_x = (2 * (x + 0.5) / (double)scene->width - 1) * aspect_ratio * fov_coeff;
	p_y = (1 - 2 * (y + 0.5) / (double)scene->height) * fov_coeff;
	origin = create_v3(0, 0, 0);
	origin = multiply_by_matrix(origin, c2w);
	direction = create_v3(p_x, p_y, -1);
	direction = multiply_by_matrix(direction, c2w);
	normalize_vector(&direction);

	return (create_ray(create_v3(0, 0, 0), direction));
}