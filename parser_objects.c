/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 18:39:49 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 18:40:02 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_sphere(char *line, t_scene *scene)
{
	int			i;
	int			move;
	t_object	*object;
	t_sphere	*sphere;

	object = malloc(sizeof(t_object));
	sphere = malloc(sizeof(t_sphere));
	i = 2;
	sphere->center.x = atod_len(&line[i], &move);
	i += move + 1;
	sphere->center.y = atod_len(&line[i], &move);
	i += move + 1;
	sphere->center.z = atod_len(&line[i], &move);
	i += move;
	sphere->radius = atod_len(&line[i], &move) / 2;
	i += move;
	parse_color(object, line, &i, &move);
	object->type = SPHERE;
	object->ptr = sphere;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	parse_square(char *line, t_scene *scene)
{
	int			i;
	int			move;
	t_object	*object;
	t_square	*square;

	object = malloc(sizeof(t_object));
	square = malloc(sizeof(t_square));
	i = 2;
	parse_coordinates(&(square->center), line, &i, &move);
	parse_coordinates(&(square->normal), line, &i, &move);
	square->length = atod_len(&line[i], &move);
	i += move;
	parse_color(object, line, &i, &move);
	object->type = SQUARE;
	object->ptr = square;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	parse_triangle(char *line, t_scene *scene)
{
	int			i;
	int			move;
	t_object	*object;
	t_triangle	*triangle;

	object = malloc(sizeof(t_object));
	triangle = malloc(sizeof(t_triangle));
	i = 2;
	parse_coordinates(&(triangle->a), line, &i, &move);
	parse_coordinates(&(triangle->b), line, &i, &move);
	parse_coordinates(&(triangle->c), line, &i, &move);
	parse_color(object, line, &i, &move);
	object->type = TRIANGLE;
	object->ptr = triangle;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	parse_cylinder(char *line, t_scene *scene)
{
	int			i;
	int			move;
	t_object	*object;
	t_cylinder	*cylinder;

	object = malloc(sizeof(t_object));
	cylinder = malloc(sizeof(t_cylinder));
	i = 2;
	parse_coordinates(&(cylinder->p), line, &i, &move);
	parse_coordinates(&(cylinder->normal), line, &i, &move);
	cylinder->radius = atod_len(&line[i], &move) / 2;
	i += move;
	cylinder->height = atod_len(&line[i], &move);
	i += move;
	parse_color(object, line, &i, &move);
	object->type = CYLINDER;
	object->ptr = cylinder;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	parse_plane(char *line, t_scene *scene)
{
	int			i;
	int			move;
	t_object	*object;
	t_plane		*plane;

	object = malloc(sizeof(t_object));
	plane = malloc(sizeof(t_plane));
	i = 2;
	parse_coordinates(&(plane->p0), line, &i, &move);
	parse_coordinates(&(plane->normal), line, &i, &move);
	parse_color(object, line, &i, &move);
	object->type = PLANE;
	object->ptr = plane;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}