/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_directives.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 18:37:52 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 18:40:28 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_resolution(char *line, t_scene *scene)
{
	int i;

	if (scene->width != 0 || scene->height != 0)
		handle_error("You can only specify resolution once in a scene.");
	scene->width = ft_atoi_len(&line[1], &i);
	scene->height = ft_atoi_len(&line[i + 1], &i);
}

void	parse_ambient(char *line, t_scene *scene)
{
	int	i;
	int	move;

	if (scene->ambient_color.red != -1)
		handle_error("You can only specify ambient light once in a scene.");
	i = 1;
	scene->ambient_intensity = atod_len(&line[i], &move);
	i += move;
	scene->ambient_color.red = (double)ft_atoi_len(&line[i], &move) / 256;
	i += move + 1;
	scene->ambient_color.green = (double)ft_atoi_len(&line[i], &move) / 256;
	i += move + 1;
	scene->ambient_color.blue = (double)ft_atoi_len(&line[i], &move) / 256;
}

void	parse_camera(char *line, t_scene *scene)
{
	int			i;
	int			move;
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	i = 1;
	parse_coordinates(&(camera->origin), line, &i, &move);
	parse_coordinates(&(camera->direction), line, &i, &move);
	camera->fov = ft_atoi_len(&line[i], &move);
	ft_lstadd_back(&(scene->cameras), ft_lstnew(camera));
}

void	parse_light(char *line, t_scene *scene)
{
	int		i;
	int		move;
	t_light	*light;
	t_color	color;

	light = malloc(sizeof(t_light));
	i = 1;
	parse_coordinates(&(light->p0), line, &i, &move);
	light->intensity = atod_len(&line[i], &move);
	i += move;
	color.red = ft_atoi_len(&line[i], &move);
	i += move + 1;
	color.green = ft_atoi_len(&line[i], &move);
	i += move + 1;
	color.blue = ft_atoi_len(&line[i], &move);
	light->color = from_rgb(color.red, color.green, color.blue);
	ft_lstadd_back(&(scene->lights), ft_lstnew(light));
}
