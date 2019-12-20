/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:41:19 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 18:41:51 by ashishae         ###   ########.fr       */
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

t_color2		light_contribution(t_light light, t_v3 hit_point, t_v3 hit_normal, t_list *objects, t_object *closest_object, t_ray sent)
{
	t_object	*closest_object2;
	double		t;
	t_v3		light_vector;
	t_v3		light_ray;
	t_ray		lray;
	int			color_result = 0;
	double		coeff = 0;
	double		specular_coeff = 0;
	double		to_light;
	t_v3		reflectance_vector;

	t_color2 result;

	light_vector = substract(light.p0, hit_point);

	light_ray = substract(light.p0, hit_point);
	to_light = vector_len(light_ray);
	normalize_vector(&light_ray);
	normalize_vector(&light_vector);

	t_color2 light_color;
	light_color = color2_coeff(light.color, light.intensity);
	t_color2 object_color;
	object_color = color2_coeff(closest_object->color, closest_object->albedo);
	t_color2 specular_color;



	lray = create_ray(v3_add(hit_point, v3_multiply(hit_normal, 0.1)), light_ray);
	if (!intersect_with_all(objects, lray, &closest_object2, &t) || t > to_light || t < 0)
	{

		coeff = fmax(0, dot_product(hit_normal, light_vector));
		reflectance_vector = substract(
										v3_multiply(
											v3_multiply(hit_normal,
											dot_product(
												sent.direction,
												hit_normal)) ,2), sent.direction);
		//reflectance_vector = substract(create_v3(0, 0, 0), reflectance_vector);
		specular_coeff = fmax(0, dot_product(
									reflectance_vector,
										sent.direction));

		t_color2 specular_color = color2_add(
									color2_coeff(object_color, 0.1),
									(color2_coeff(int_color(0xffffff), 0.9)));
		//specular_coeff = pow(specular_coeff, 3);
		//printf("%f\n", specular_coeff);
		//coeff *= closest_object->albedo * light.intensity;
	}
	result = color2_coeff(color2_mult(light_color, object_color), coeff);
	//result = color2_add(result, color2_coeff(color2_mult(light_color, specular_color), specular_coeff));
	return (result);
}

t_color2		shade(t_scene *scene, t_ray sent, t_object *closest_object, double t_min)
{
	t_v3	hit_point;
	t_v3	hit_normal;
	t_list *runner;
	//double coeff = 0;
	t_color2 result;
	t_color2 addition;
	result = int_color(0);

	hit_point = v3_add(sent.origin, v3_multiply(sent.direction, t_min));
	hit_normal = get_normal(hit_point, closest_object);
	if (dot_product(sent.direction, hit_normal) > 0)
	 	hit_normal = substract(create_v3(0, 0, 0), v3_multiply(hit_normal, 1));
	runner = scene->lights;
	while (runner != NULL)
	{
		addition = light_contribution(*(t_light *)(runner->content), hit_point, hit_normal, scene->objects, closest_object, sent);
		result = color2_add(result, addition);
		//coeff += light_contribution(*(t_light *)(runner->content), hit_point, hit_normal, objects, closest_object);
		runner = runner->next;
	}
	return (result);
}

int		get_color(t_scene *scene, t_ray sent)
{

	double t_min;

	t_object *closest_object;
	t_object *closest_object2;

	t_light	light;
	double coeff;
	int		amb_color = 0xffffff;
	//printf("amb_color is %d\n", amb_color);
	double		amb_intensity = 0.1;
	int color_result = 0;
	t_color2 result;
	t_color2 addition;

	if (intersect_with_all(scene->objects, sent, &closest_object, &t_min))
	{

		addition = shade(scene, sent, closest_object, t_min);
		// coeff = shade(objects, lights, sent, closest_object, t_min);
		// amb_color = color_coefficient(0xff, amb_intensity);
		// color_result = color_coefficient(closest_object->color, fmin(0.99, coeff));
		// double ambient_max = 0.90 - fmin(0.99, coeff);


		t_color2 ambient_color = color2_coeff(scene->ambient_color, scene->ambient_intensity);
		//printf("ambient: R %f G %f B %f\n", ambient_color.red, ambient_color.green, ambient_color.blue);
		t_color2 object_color = closest_object->color;



		t_color2 ambient_component = color2_mult(object_color, ambient_color);

		result = color2_add(ambient_component, addition);
		color_result = to_int(result);

		return (color_result);
	}
	else
		return (0);
}