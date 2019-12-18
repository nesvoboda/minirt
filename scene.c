/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:57:12 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/18 17:11:49 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "v3.h"
#include "list.h"
#include "minirt.h"

t_light *new_light(int color, double intensity, t_v3 p0)
{
	t_light *light;

	light = malloc(sizeof(t_light));
	light->color = color;
	light->intensity = intensity;
	light->p0 = p0;
	return (light);
}

t_object	*new_object(otype type, void *ptr, int color)
{
	t_object *result;
	result = malloc(sizeof(t_object));
	result->type = type;
	result->ptr = ptr;
	result->color = color;
	result->albedo = 0.8;
	return (result);
}

t_list		*get_objects()
{
	t_list *result = NULL;
	t_object *object;

	// object = new_object(SPHERE,
	// 	new_sphere(create_v3(-2, -1, -5), 0.5), 0xff0000);
	// ft_lstadd_back(&result, ft_lstnew(object));

	// object = new_object(SPHERE,
	// 	new_sphere(create_v3(0, -2, -4), 0.5), 0xff0000);
	// ft_lstadd_back(&result, ft_lstnew(object));

	t_v3 plane_vector = create_v3(0, 1, 0);
	normalize_vector(&plane_vector);

	t_v3 square_vector = create_v3(0, -0.5, 0.5);
	normalize_vector(&square_vector);


	object = new_object(PLANE,
		new_plane(create_v3(0, -3, -10), plane_vector), 0xffa500);
	ft_lstadd_back(&result, ft_lstnew(object));

	// object = new_object(TRIANGLE, new_triangle(create_v3(0,-1,-3), create_v3(2,-1, -5), create_v3(-2,-1,-5)), 0xff);
	// ft_lstadd_back(&result, ft_lstnew(object));

	// object = new_object(SQUARE,
	// 	new_square(create_v3(0, 0, -5), square_vector, 2), 0xff);
	// ft_lstadd_back(&result, ft_lstnew(object));

	object = new_object(CYLINDER,
	new_cylinder(create_v3(0, -2, -5), plane_vector, 2, 1), 0xff);
	ft_lstadd_back(&result, ft_lstnew(object));

	return (result);
}

t_list		*get_lights()
{
	t_list *result = NULL;
	t_light *light;

	light = new_light(0xffffff, 0.5, create_v3(-5, 5, -4));
	ft_lstadd_back(&result, ft_lstnew(light));
	light = new_light(0xffffff, 0.5, create_v3(5, 5, -4));
	ft_lstadd_back(&result, ft_lstnew(light));
	light = new_light(0xffffff, 0.5, create_v3(-3, 0, 4));
	ft_lstadd_back(&result, ft_lstnew(light));
	return (result);
}
