/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:06:27 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/15 19:09:46 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int		allowed_symbol(char c)
{
	if (c == '\t' | c == ' ' | c == '\n' | c == '.' || c == ',' ||
	(c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}

int		check_line(char *line)
{
	int i;

	i = 3;
	while (line[i])
	{
		if (!allowed_symbol(line[i]))
			return (0);
		i++;
	}
	return (1);
}
