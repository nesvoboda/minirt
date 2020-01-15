/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 18:34:29 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/15 17:53:02 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	handle_error(char *errormsg)
{
	write(2, "Error\n", 6);
	write(2, errormsg, ft_strlen(errormsg));
	write(2, "\n", 1);
	exit(-1);
}

int		open_file(char *path)
{
	int			fd;
	extern int	errno;
	char		*msg;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error(strerror(errno));
	return (fd);
}

void	parse_color(t_object *object, char *line, int *i, int *move)
{
	object->color.red = (float)ft_atoi_len(&line[*i], move) / 256;
	*i += *move + 1;
	object->color.green = (float)ft_atoi_len(&line[*i], move) / 256;
	*i += *move + 1;
	object->color.blue = (float)ft_atoi_len(&line[*i], move) / 256;
	object->albedo = 1;
}

void	parse_coordinates(t_v3 *point, char *line, int *i, int *move)
{
	point->x = atod_len(&line[*i], move);
	*i += *move + 1;
	point->y = atod_len(&line[*i], move);
	*i += *move + 1;
	point->z = atod_len(&line[*i], move);
	*i += *move;
}

int		line_fields(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i])
		i++;
	return (i);
}
