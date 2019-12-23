/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:41:19 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 21:01:28 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shading.h"

t_v3		get_normal(t_v3 point, t_object *object)
{
	if (object->type == SPHERE)
		return (get_sphere_normal(point, *(t_sphere *)object->ptr));
	if (object->type == PLANE)
		return (get_plane_normal(*(t_plane *)object->ptr));
	if (object->type == TRIANGLE)
		return (get_triangle_normal(*(t_triangle *)object->ptr));
	if (object->type == SQUARE)
		return (get_square_normal(*(t_square *)object->ptr));
	if (object->type == CYLINDER)
		return (get_cylinder_normal(point, *(t_cylinder *)object->ptr));
}

t_color2	mix_colors(t_light light, t_object *object, double coeff)
{
	t_color2	result;
	t_color2	light_color;
	t_color2	object_color;

	light_color = color2_coeff(light.color, light.intensity);
	object_color = object->color;
	result = color2_coeff(color2_mult(light_color, object_color), coeff);
	return (result);
}

t_color2	light_contribution(t_light light, t_inter inter)
{
	t_object	*closest_object2;
	double		t;
	t_v3		light_ray;
	t_ray		lray;
	double		coeff;

	coeff = 0;
	light_ray = substract(light.p0, inter.hit_point);
	normalize_vector(&light_ray);
	lray = create_ray(v3_add(inter.hit_point,
								v3_multiply(inter.hit_normal, 0.1)), light_ray);
	if (!intersect_with_all(inter.objects, lray, &closest_object2, &t)
					|| t > vector_len(substract(light.p0, inter.hit_point)))
	{
		coeff = fmax(0, dot_product(inter.hit_normal, light_ray));
	}
	return (mix_colors(light, inter.closest_object, coeff));
}

t_color2	shade(t_scene *scene, t_ray sent, t_object *closest_object,
																double t_min)
{
	t_v3		hit_point;
	t_v3		hit_normal;
	t_list		*runner;
	t_color2	result;
	t_color2	addition;

	result = int_color(0);
	hit_point = v3_add(sent.origin, v3_multiply(sent.direction, t_min));
	hit_normal = get_normal(hit_point, closest_object);
	if (dot_product(sent.direction, hit_normal) > 0)
		hit_normal = substract(create_v3(0, 0, 0), v3_multiply(hit_normal, 1));
	runner = scene->lights;
	while (runner != NULL)
	{
		addition = light_contribution(*(t_light *)(runner->content),
		new_inter(hit_point, hit_normal, scene->objects, closest_object));
		result = color2_add(result, addition);
		runner = runner->next;
	}
	return (result);
}

int			get_color(t_scene *scene, t_ray sent)
{
	double		t_min;
	t_object	*closest_object;
	t_color2	result;
	t_color2	ambient_color;

	if (intersect_with_all(scene->objects, sent, &closest_object, &t_min))
	{
		ambient_color = color2_coeff(scene->ambient_color,
									scene->ambient_intensity);
		result = color2_add(color2_mult(closest_object->color, ambient_color),
							shade(scene, sent, closest_object, t_min));
		return (to_int(result));
	}
	else
		return (0);
}
