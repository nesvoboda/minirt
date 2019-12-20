/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 12:49:49 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 18:40:10 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <fcntl.h>
#include "get_next_line.h"
#include "scene.h"
#include "parser.h"
#include "list.h"
#include "color2.h"
#include "sphere.h"
#include "plane.h"
#include "square.h"
#include "cylinder.h"
#include "triangle.h"
#include <sys/errno.h>

int open_file(char *path)
{
	int fd;
	int errno;
	char *msg;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		msg = strerror(errno);
		write(1, msg, ft_strlen(msg));
		write(1, "\n", 1);
		return (-1);
	}
	return (fd);
}

void parse_resolution(char *line, t_scene *scene)
{
	int i;
	scene->width = ft_atoi_len(&line[1], &i);
	scene->height = ft_atoi_len(&line[i+1], &i);
}

void parse_ambient(char *line, t_scene *scene)
{
	int i;
	int move;

	i = 1;
	scene->ambient_intensity = atod_len(&line[i], &move);
	i += move;
	scene->ambient_color.red = (double) ft_atoi_len(&line[i], &move) / 256;
	i += move + 1;
	scene->ambient_color.green = (double) ft_atoi_len(&line[i], &move) / 256;
	i += move + 1;
	scene->ambient_color.blue = (double) ft_atoi_len(&line[i], &move) / 256;
}

void parse_camera(char *line, t_scene *scene)
{
	int i;
	int move;

	i = 1;
	scene->camera.origin.x = atod_len(&line[i], &move);
	i += move+1;
	scene->camera.origin.y = atod_len(&line[i], &move);
	i += move+1;
	scene->camera.origin.z = atod_len(&line[i], &move);
	i += move + 1;
	scene->camera.direction.x = atod_len(&line[i], &move);
	i += move+1;
	scene->camera.direction.y = atod_len(&line[i], &move);
	i += move+1;
	scene->camera.direction.z = atod_len(&line[i], &move);
	i += move+1;
	scene->camera.fov = ft_atoi_len(&line[i], &move);
}

void parse_light(char *line, t_scene *scene)
{
	int i;
	int move;
	t_light *light;
	int r;
	int g;
	int b;

	light = malloc(sizeof(t_light));
	i = 1;
	light->p0.x = atod_len(&line[i], &move);
	i += move+1;
	light->p0.y = atod_len(&line[i], &move);
	i += move+1;
	light->p0.z = atod_len(&line[i], &move);
	i += move;
	light->intensity = atod_len(&line[i], &move);
	i += move;
	r = ft_atoi_len(&line[i], &move);
	i += move+1;
	g = ft_atoi_len(&line[i], &move);
	i += move+1;
	b = ft_atoi_len(&line[i], &move);
	light->color = from_rgb(r, g, b);
	ft_lstadd_back(&(scene->lights), ft_lstnew(light));
}

void parse_sphere(char *line, t_scene *scene)
{
	int i;
	int move;
	t_object *object;
	t_sphere *sphere;

	object = malloc(sizeof(t_object));
	sphere = malloc(sizeof(t_sphere));
	i = 2;
	sphere->center.x = atod_len(&line[i], &move);
	i += move+1;
	sphere->center.y = atod_len(&line[i], &move);
	i += move+1;
	sphere->center.z = atod_len(&line[i], &move);
	i += move;
	sphere->radius = atod_len(&line[i], &move) / 2;
	i += move;
	object->color.red = (float)ft_atoi_len(&line[i], &move) / 256;
	i += move+1;
	object->color.green = (float)ft_atoi_len(&line[i], &move) / 256;
	i += move+1;
	object->color.blue = (float)ft_atoi_len(&line[i], &move) / 256;
	object->albedo = 1;
	object->type = SPHERE;
	object->ptr = sphere;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void parse_square(char *line, t_scene *scene)
{
	int i;
	int move;
	t_object *object;
	t_square *square;

	object = malloc(sizeof(t_object));
	square = malloc(sizeof(t_square));
	i = 2;
	square->center.x = atod_len(&line[i], &move);
	i += move+1;
	square->center.y = atod_len(&line[i], &move);
	i += move+1;
	square->center.z = atod_len(&line[i], &move);
	i += move;
	square->normal.x = atod_len(&line[i], &move);
	i += move+1;
	square->normal.y = atod_len(&line[i], &move);
	i += move+1;
	square->normal.z = atod_len(&line[i], &move);
	i += move;
	square->length = atod_len(&line[i], &move);
	i += move;
	object->color.red = (float)ft_atoi_len(&line[i], &move) / 256;
	i += move+1;
	object->color.green = (float)ft_atoi_len(&line[i], &move) / 256;
	i += move+1;
	object->color.blue = (float)ft_atoi_len(&line[i], &move) / 256;
	object->albedo = 1;
	object->type = SQUARE;
	object->ptr = square;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void parse_triangle(char *line, t_scene *scene)
{
	int i;
	int move;
	t_object *object;
	t_triangle *triangle;

	object = malloc(sizeof(t_object));
	triangle = malloc(sizeof(t_triangle));
	i = 2;
	triangle->a.x = atod_len(&line[i], &move);
	i += move+1;
	triangle->a.y = atod_len(&line[i], &move);
	i += move+1;
	triangle->a.z = atod_len(&line[i], &move);
	i += move;
	triangle->b.x = atod_len(&line[i], &move);
	i += move+1;
	triangle->b.y = atod_len(&line[i], &move);
	i += move+1;
	triangle->b.z = atod_len(&line[i], &move);
	i += move;
	triangle->c.x = atod_len(&line[i], &move);
	i += move+1;
	triangle->c.y = atod_len(&line[i], &move);
	i += move+1;
	triangle->c.z = atod_len(&line[i], &move);
	i += move;
	object->color.red = (float)ft_atoi_len(&line[i], &move) / 256;
	i += move+1;
	object->color.green = (float)ft_atoi_len(&line[i], &move) / 256;
	i += move+1;
	object->color.blue = (float)ft_atoi_len(&line[i], &move) / 256;
	object->albedo = 1;
	object->type = TRIANGLE;
	object->ptr = triangle;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void parse_cylinder(char *line, t_scene *scene)
{
	int i;
	int move;
	t_object *object;
	t_cylinder *cylinder;

	object = malloc(sizeof(t_object));
	cylinder = malloc(sizeof(t_cylinder));
	i = 2;
	cylinder->p.x = atod_len(&line[i], &move);
	i += move+1;
	cylinder->p.y = atod_len(&line[i], &move);
	i += move+1;
	cylinder->p.z = atod_len(&line[i], &move);
	i += move;
	cylinder->normal.x = atod_len(&line[i], &move);
	i += move+1;
	cylinder->normal.y = atod_len(&line[i], &move);
	i += move+1;
	cylinder->normal.z = atod_len(&line[i], &move);
	i += move;
	cylinder->radius = atod_len(&line[i], &move) / 2;
	i += move;
	cylinder->height = atod_len(&line[i], &move);
	i += move;
	object->color.red = (float)ft_atoi_len(&line[i], &move) / 256;
	i += move+1;
	object->color.green = (float)ft_atoi_len(&line[i], &move) / 256;
	i += move+1;
	object->color.blue = (float)ft_atoi_len(&line[i], &move) / 256;
	object->albedo = 1;
	object->type = CYLINDER;
	object->ptr = cylinder;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void parse_plane(char *line, t_scene *scene)
{
	int i;
	int move;
	t_object *object;
	t_plane *plane;

	object = malloc(sizeof(t_object));
	plane = malloc(sizeof(t_plane));
	i = 2;
	plane->p0.x = atod_len(&line[i], &move);
	i += move+1;
	plane->p0.y = atod_len(&line[i], &move);
	i += move+1;
	plane->p0.z = atod_len(&line[i], &move);
	i += move;
	plane->normal.x = atod_len(&line[i], &move);
	i += move+1;
	plane->normal.y = atod_len(&line[i], &move);
	i += move+1;
	plane->normal.z = atod_len(&line[i], &move);
	i += move;
	object->color.red = (float)ft_atoi_len(&line[i], &move) / 256;
	i += move+1;
	object->color.green = (float)ft_atoi_len(&line[i], &move) / 256;
	i += move+1;
	object->color.blue = (float)ft_atoi_len(&line[i], &move) / 256;
	object->albedo = 1;
	object->type = PLANE;
	object->ptr = plane;
	ft_lstadd_back(&(scene->objects), ft_lstnew(object));
}

void	parse_line(char *line, t_scene *scene)
{
	if (line[0] == '\0')
		return ;
		char first = line[0];
	char second = line[1];
	if (first == 'R')
		parse_resolution(line, scene);
	else if (first == 'A')
		parse_ambient(line, scene);
	else if (first == 'c' && second != 'y')
		parse_camera(line, scene);
	else if (first == 'l')
		parse_light(line, scene);
	else if (first == 's' && second == 'p')
		parse_sphere(line, scene);
	else if (first == 'p' && second == 'l')
		parse_plane(line, scene);
	else if (first == 's' && second == 'q')
		parse_square(line, scene);
	else if (first == 'c' && second == 'y')
		parse_cylinder(line, scene);
	else if (first == 't' && second == 'r')
		parse_triangle(line, scene);
}

t_scene *parse_file(char *path)
{
	int fd;
	int ret;
	char *line = "";
	t_scene *scene;


	fd = open_file(path);
	if (fd == -1)
		return (0);
	scene = malloc(sizeof(t_scene));
	scene->objects = NULL;
	scene->lights = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
		parse_line(line, scene);

	parse_line(line, scene);
	// check scene
	//scene->objects = get_objects();
	//scene->lights = get_lights();
	close(fd);
	return (scene);
}