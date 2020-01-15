/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:27:06 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/15 19:06:56 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>
# include "get_next_line.h"
# include "minirt.h"
# include "ft_atoi_len.h"

t_scene	*parse_file(char *path);
void	check_scene(t_scene *scene);
void	init_scene(t_scene *scene);
void	parse_line(char *line, t_scene *scene, char **splitted);
void	parse_coordinates(t_v3 *point, char *line, int *i, int *move);
void	parse_color(t_object *object, char *line, int *i, int *move);
int		open_file(char *path);
void	handle_error(char *errormsg);
void	parse_sphere(char *line, t_scene *scene);
void	parse_square(char *line, t_scene *scene);
void	parse_triangle(char *line, t_scene *scene);
void	parse_cylinder(char *line, t_scene *scene);
void	parse_plane(char *line, t_scene *scene);
void	parse_resolution(char *line, t_scene *scene, char **splitted);
void	parse_ambient(char *line, t_scene *scene, char **splitted);
void	parse_camera(char *line, t_scene *scene, char **splitted);
void	parse_light(char *line, t_scene *scene, char **splitted);
char	**ft_split(char const *s, char c);
int		line_fields(char **splitted);
int		check_color2(t_color2 c);
void	parse_color2(t_color2 *result, char *field, char *errmsg);
void	parse_coords(t_v3 *point, char *field, char *errmsg);
int		check_normal(t_v3 n);
void	check_scene(t_scene *scene);
int		allowed_symbol(char c);
int		check_line(char *line);

#endif
