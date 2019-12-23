/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:27:06 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 18:48:50 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <fcntl.h>
#include "get_next_line.h"
#include "minirt.h"
#include "ft_atoi_len.h"
#include <sys/errno.h>

t_scene	*parse_file(char *path);
void	check_scene(t_scene *scene);
void	init_scene(t_scene *scene);
void	parse_line(char *line, t_scene *scene);
void	parse_coordinates(t_v3 *point, char *line, int *i, int *move);
void	parse_color(t_object *object, char *line, int *i, int *move);
int		open_file(char *path);
void	handle_error(char *errormsg);
void	parse_sphere(char *line, t_scene *scene);
void	parse_square(char *line, t_scene *scene);
void	parse_triangle(char *line, t_scene *scene);
void	parse_cylinder(char *line, t_scene *scene);
void	parse_plane(char *line, t_scene *scene);
void	parse_resolution(char *line, t_scene *scene);
void	parse_ambient(char *line, t_scene *scene);
void	parse_camera(char *line, t_scene *scene);
void	parse_light(char *line, t_scene *scene);


#endif