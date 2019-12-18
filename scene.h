/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:57:28 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/18 10:06:43 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "v3.h"
# include "list.h"

typedef enum object_type
{
	SPHERE,
	CUBE,
	PLANE,
	LIGHT,
	TRIANGLE,
	SQUARE,
	CYLINDER,
}		otype;

typedef struct	s_object
{
	otype	type;
	void *ptr;
	int color;
	double	albedo;

}				t_object;

typedef struct s_light
{
	t_v3 p0;
	double intensity;
	int color;
}				t_light;

t_light			*new_light(int color, double intensity, t_v3 p0);
t_object		*new_object(otype type, void *ptr, int color);
t_list			*get_objects();
t_list			*get_lights();

#endif