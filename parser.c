/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 12:49:49 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 18:47:52 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_line(char *line, t_scene *scene)
{
	char	first;
	char	second;

	if (line[0] == '\0')
		return ;
	first = line[0];
	second = line[1];
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

void	init_scene(t_scene *scene)
{
	scene->cameras = NULL;
	scene->lights = NULL;
	scene->height = 0;
	scene->width = 0;
	scene->ambient_color.red = -1;
	scene->ambient_color.green = -1;
	scene->ambient_color.blue = -1;
}

void	check_scene(t_scene *scene)
{
	if (scene->cameras == NULL)
		handle_error("You need to have at least one camera in a scene.");
	if (scene->ambient_color.red < 0 || scene->ambient_color.green < 0
	|| scene->ambient_color.blue < 0)
		handle_error("You need to specify a valid ambient light ([0-255]).");
	if (scene->width <= 0 || scene->height <= 0)
		handle_error("You have to specify positive width and height.");
	if (scene->width > 2560)
		scene->width = 2560;
	if (scene->height > 1440)
		scene->height = 1440;
}

t_scene	*parse_file(char *path)
{
	int		fd;
	int		ret;
	char	*line;
	t_scene	*scene;

	fd = open_file(path);
	if (fd == -1)
		return (0);
	scene = malloc(sizeof(t_scene));
	init_scene(scene);
	scene->objects = NULL;
	scene->lights = NULL;
	scene->cameras = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		parse_line(line, scene);
		free(line);
	}
	parse_line(line, scene);
	free(line);
	check_scene(scene);
	close(fd);
	return (scene);
}
