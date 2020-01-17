/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_directives.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 18:37:52 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/17 18:58:04 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	parse_resolution(t_scene *scene, char **splitted)
{
	if (scene->width != 0 || scene->height != 0)
		handle_error("You can only specify resolution once in a scene.");
	if (line_fields(splitted) != 3)
		handle_error("You have to add both height and width in R.");
	scene->width = ft_atoi(splitted[1]);
	scene->height = ft_atoi(splitted[2]);
}

void	parse_ambient(t_scene *scene, char **splitted)
{
	if (scene->ambient_color.red != -1)
		handle_error("You can only specify ambient light once in a scene.");
	if (line_fields(splitted) != 3)
		handle_error("Ambient light usage: A [ratio] [R,G,B]");
	scene->ambient_intensity = ft_atod(splitted[1]);
	if (scene->ambient_intensity < 0 || scene->ambient_intensity > 1)
		handle_error("Ambient light intensity must be in range [0.0,1.0].");
	parse_color2(&(scene->ambient_color), splitted[2],
					"Ambient light format: R,G,B.");
	if (!check_color2(scene->ambient_color))
		handle_error("Ambient color components must be in range [0-255].");
}

void	parse_camera(t_scene *scene, char **splitted)
{
	t_camera	*camera;
	char		*errmsg;

	errmsg = "Camera usage: c [origin x,y,z] [normal: x,y,z] [fov].";
	if (line_fields(splitted) != 4)
		handle_error(errmsg);
	camera = malloc(sizeof(t_camera));
	parse_coords(&(camera->origin), splitted[1], errmsg);
	parse_coords(&(camera->direction), splitted[2], errmsg);
	normalize_vector(&(camera->direction));
	camera->fov = ft_atoi(splitted[3]);
	if (camera->fov < 0 || camera->fov > 180)
		handle_error("Camera FOV must be in range [0-180].");
	ft_lstadd_back(&(scene->cameras), ft_lstnew(camera));
}

void	parse_light(t_scene *scene, char **splitted)
{
	t_light	*light;
	char	*errmsg;

	errmsg = "Light usage: l [origin x,y,z] [brightness] [color R,G,B].";
	if (line_fields(splitted) != 4)
		handle_error(errmsg);
	light = malloc(sizeof(t_light));
	parse_coords(&(light->p0), splitted[1], errmsg);
	light->intensity = ft_atod(splitted[2]);
	parse_color2(&(light->color), splitted[3], "Light color format: R,G,B.");
	if (!check_color2(light->color))
		handle_error("Light color comps must be in range [0-255].");
	ft_lstadd_back(&(scene->lights), ft_lstnew(light));
}
