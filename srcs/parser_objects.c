/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 18:39:49 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/17 18:58:10 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	parse_sphere(t_scene *scene, char **splitted)
{
	t_object	*object;
	t_sphere	*sphere;
	char		*errmsg;

	errmsg = "Sphere format: sp [origin x,y,z] [diameter] [R,G,B]";
	if (line_fields(splitted) != 4)
		handle_error(errmsg);
	object = malloc(sizeof(t_object));
	sphere = malloc(sizeof(t_sphere));
	parse_coords(&(sphere->center), splitted[1], errmsg);
	sphere->radius = ft_atod(splitted[2]) / 2;
	parse_color2(&(object->color), splitted[3], "Sphere color format [R,G,B]");
	if (!check_color2(object->color))
		handle_error("Sphere color components must be in range [0-255]");
	object->type = SPHERE;
	object->ptr = sphere;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	parse_square(t_scene *scene, char **splitted)
{
	t_object	*object;
	t_square	*square;
	char		*errormsg;

	errormsg = "Square usage: sq [origin x,y,z] [normal x,y,z] [side] [R,G,B]";
	if (line_fields(splitted) != 5)
		handle_error(errormsg);
	object = malloc(sizeof(t_object));
	square = malloc(sizeof(t_square));
	parse_coords(&(square->center), splitted[1], errormsg);
	parse_coords(&(square->normal), splitted[2], errormsg);
	normalize_vector(&(square->normal));
	square->length = ft_atod(splitted[3]);
	parse_color2(&(object->color), splitted[4], "Square color format [R,G,B]");
	if (!check_color2(object->color))
		handle_error("Square color components must be in range [0-255]");
	object->type = SQUARE;
	object->ptr = square;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	parse_triangle(t_scene *scene, char **splitted)
{
	t_object	*object;
	t_triangle	*triangle;
	char		*errormsg;

	errormsg = "Triangle usage: tr [x,y,z] [x,y,z] [x,y,z] [R,G,B]";
	if (line_fields(splitted) != 5)
		handle_error(errormsg);
	object = malloc(sizeof(t_object));
	triangle = malloc(sizeof(t_triangle));
	parse_coords(&(triangle->a), splitted[1], errormsg);
	parse_coords(&(triangle->b), splitted[2], errormsg);
	parse_coords(&(triangle->c), splitted[3], errormsg);
	parse_color2(&(object->color), splitted[4], "Tr color format [R,G,B]");
	if (!check_color2(object->color))
		handle_error("Triangle color comps must be in range [0-255");
	object->type = TRIANGLE;
	object->ptr = triangle;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	parse_cylinder(t_scene *scene, char **splitted)
{
	t_object	*object;
	t_cylinder	*cylinder;
	char		*errormsg;

	errormsg = "Cylinder usage: cy [x,y,z] [normal x,y,z] [d] [h] [R,G,B]";
	if (line_fields(splitted) != 6)
		handle_error(errormsg);
	object = malloc(sizeof(t_object));
	cylinder = malloc(sizeof(t_cylinder));
	parse_coords(&(cylinder->p), splitted[1], errormsg);
	parse_coords(&(cylinder->normal), splitted[2], errormsg);
	normalize_vector(&cylinder->normal);
	cylinder->radius = ft_atod(splitted[3]) / 2;
	cylinder->height = ft_atod(splitted[4]);
	parse_color2(&object->color, splitted[5], "cy color format [R,G,B]");
	if (!check_color2(object->color))
		handle_error("Cylinder color comps must be in range [0-255]");
	object->type = CYLINDER;
	object->ptr = cylinder;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	parse_plane(t_scene *scene, char **splitted)
{
	t_object	*object;
	t_plane		*plane;
	char		*errormsg;

	errormsg = "Plane usage: pl [x,y,z] [normal x,y,z] [R,G,B]";
	if (line_fields(splitted) != 4)
		handle_error(errormsg);
	object = malloc(sizeof(t_object));
	plane = malloc(sizeof(t_plane));
	parse_coords(&plane->p0, splitted[1], errormsg);
	parse_coords(&plane->normal, splitted[2], errormsg);
	normalize_vector(&plane->normal);
	parse_color2(&object->color, splitted[3], "Plane color format [R,G,B]");
	if (!check_color2(object->color))
		handle_error("Plane color comps must be in range [0-255]");
	object->type = PLANE;
	object->ptr = plane;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}
