/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:57:28 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/21 18:54:46 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "v3.h"
# include "list.h"
# include "color.h"
# include "color2.h"

typedef struct s_camera
{
	t_v3	origin;
	t_v3	direction;
	int		fov;
}				t_camera;

typedef struct s_scene
{
	t_list		*objects;
	t_list		*lights;
	int			width;
	int			height;
	double		ambient_intensity;
	t_color2	ambient_color;
	t_list		*cameras;
	int			selected_camera;
}				t_scene;



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
	void	*ptr;
	t_color2		color;
	double	albedo;

}				t_object;

typedef struct s_light
{
	t_v3 p0;
	double intensity;
	t_color2 color;
}				t_light;

t_light			*new_light(t_color2 color, double intensity, t_v3 p0);
t_object		*new_object(otype type, void *ptr, t_color2 color);
t_list			*get_objects();
t_list			*get_lights();
t_scene			*get_scene();

#endif