/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:25:35 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 19:36:33 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "minirt.h"
#include "matrix.h"

t_ray		create_ray(t_v3 origin, t_v3 direction)
{
	t_ray result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

t_camera	pick_camera(t_scene *scene)
{
	t_list	*runner;
	int		i;

	i = 0;
	runner = scene->cameras;
	while (i < scene->selected_camera && runner != NULL)
	{
		i++;
		runner = runner->next;
	}
	return (*(t_camera *)runner->content);
}

t_v3		get_direction(int x, int y, t_scene *scene, t_camera camera)
{
	double fov_coeff;
	double aspect_ratio;
	double p_x;
	double p_y;

	fov_coeff = tan((double)camera.fov / 2 * M_PI / 180);
	aspect_ratio = (double)scene->width / (double)scene->height;
	p_x = (2 * (x + 0.5) / (double)scene->width - 1) * aspect_ratio * fov_coeff;
	p_y = (1 - 2 * (y + 0.5) / (double)scene->height) * fov_coeff;
	return (create_v3(p_x, p_y, 1));
}

t_ray		ray_to_pixel(int x, int y, t_scene *scene)
{
	t_v3		origin;
	t_v3		direction;
	t_matrix	c2w;
	t_camera	camera;

	camera = pick_camera(scene);
	c2w = look_at(camera.origin, camera.direction);
	origin = multiply_by_matrix(create_v3(0, 0, 0), c2w);
	direction = get_direction(x, y, scene, camera);
	direction = multiply_by_matrix(direction, c2w);
	direction = substract(direction, origin);
	normalize_vector(&direction);
	return (create_ray(origin, direction));
}
