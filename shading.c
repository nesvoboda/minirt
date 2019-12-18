/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:41:19 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/18 10:08:40 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shading.h"

t_v3	get_normal(t_v3 point, t_object *object)
{
	if (object->type == SPHERE)
	{
		//printf("Entered sphere normal\n");
		return (get_sphere_normal(point, *(t_sphere *)object->ptr));
	}
	if (object->type == PLANE)
	{
		//printf("Entered\n");
		return (get_plane_normal(*(t_plane *)object->ptr));
	}
	if (object->type == TRIANGLE)
	{
		//printf("Entered triangle normal\n");
		return (get_triangle_normal(*(t_triangle *)object->ptr));
	}
	if (object->type == SQUARE)
	{
		//printf("Entered triangle normal\n");
		return (get_square_normal(*(t_square *)object->ptr));
	}
	if (object->type == CYLINDER)
		return (get_cylinder_normal(point, *(t_cylinder *)object->ptr));
}

double		light_contribution(t_light light, t_v3 hit_point, t_v3 hit_normal, t_list *objects, t_object *closest_object)
{
	t_object	*closest_object2;
	double		t;
	t_v3		light_vector;
	t_v3		light_ray;
	t_ray		lray;
	int			color_result = 0;
	double		coeff = 0;
	double		to_light;

	light_vector = substract(light.p0, hit_point);
	light_ray = substract(light.p0, hit_point);
	to_light = vector_len(light_ray);
	normalize_vector(&light_ray);
	normalize_vector(&light_vector);


	lray = create_ray(v3_add(hit_point, v3_multiply(hit_normal, 0.00001)), light_ray);
	if (!intersect_with_all(objects, lray, &closest_object2, &t) || t > to_light)
	{

		coeff = fmax(0, dot_product(hit_normal, light_vector));
		coeff *= closest_object->albedo * light.intensity;
	}
	else if (closest_object->type == SQUARE)
	{
		printf("Collision! t: %f\n", t);
		printf("Collided with: %d\n", closest_object2->type);
	}
	return (coeff);
}

double		shade(t_list *objects, t_list *lights, t_ray sent, t_object *closest_object, double t_min)
{
	t_v3	hit_point;
	t_v3	hit_normal;
	t_list *runner;
	double coeff = 0;

	hit_point = v3_add(sent.origin, v3_multiply(sent.direction, t_min));
	hit_normal = get_normal(hit_point, closest_object);
	runner = lights;
	while (runner != NULL)
	{
		if (closest_object->type == SQUARE)
			printf("normal: %f %f %f\n", hit_normal.x, hit_normal.y, hit_normal.z);
		coeff += light_contribution(*(t_light *)(runner->content), hit_point, hit_normal, objects, closest_object);
		runner = runner->next;
	}
	return (coeff);
}

int		get_color(t_list *objects, t_list *lights, t_ray sent)
{

	double t_min;

	t_object *closest_object;
	t_object *closest_object2;

	t_light	light;
	double coeff;
	int		amb_color = 0xffffff;
	double		amb_intensity = 0.5;
	int color_result = 0;

	if (intersect_with_all(objects, sent, &closest_object, &t_min))
	{

		coeff = shade(objects, lights, sent, closest_object, t_min);
		amb_color = color_coefficient(0xff, amb_intensity);
		color_result = color_coefficient(closest_object->color, fmin(0.99, coeff));
		double ambient_max = 0.90 - fmin(0.99, coeff);

		return (color_result);
	}
	else
		return (0);
}