/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 12:49:49 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/15 19:07:47 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_line(char *line, t_scene *scene, char **splitted)
{
	char	first;
	char	second;

	first = line[0];
	second = line[1];
	if (first == 'R')
		parse_resolution(line, scene, splitted);
	else if (first == 'A')
		parse_ambient(line, scene, splitted);
	else if (first == 'c' && second != 'y')
		parse_camera(line, scene, splitted);
	else if (first == 'l')
		parse_light(line, scene, splitted);
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
	else if (first != '\n' && first != '\0')
		handle_error("Unknown element in the scene.");
}

void	init_scene(t_scene *scene)
{
	scene->cameras = NULL;
	scene->lights = NULL;
	scene->objects = NULL;
	scene->height = 0;
	scene->width = 0;
	scene->ambient_color.red = -1;
	scene->ambient_color.green = -1;
	scene->ambient_color.blue = -1;
}

t_scene	*parse_file(char *path)
{
	int		fd;
	int		ret;
	char	*line;
	t_scene	*scene;
	char	**splitted;

	fd = open_file(path);
	if (fd == -1)
		return (0);
	scene = malloc(sizeof(t_scene));
	init_scene(scene);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		splitted = ft_split(line, ' ');
		if (!check_line(line))
			handle_error("Forbidden symbol in the scene.");
		parse_line(line, scene, splitted);
		free(line);
	}
	parse_line(line, scene, splitted);
	free(line);
	check_scene(scene);
	close(fd);
	return (scene);
}
