/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:51:24 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 13:46:30 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <math.h>
# include "v3.h"
# include "ray.h"
# include "list.h"
# include "color.h"
# include "sphere.h"
# include "triangle.h"
# include "plane.h"
# include "scene.h"
# include "square.h"
# include "cylinder.h"
# include "intersect.h"
# include "shading.h"
# include "color2.h"
# include "bmp.h"
# include "get_next_line.h"
# include "parser.h"
# include "ft_atoi_len.h"
# include <stdlib.h>
# define IMG_HEIGHT 1000
# define IMG_WIDTH 1000
# define FOV 90


typedef struct  s_image {
    void        *img;
    int        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_image;

typedef struct s_info
{
	t_scene		*scene;
	int			camera_number;
	void		*id;
	void		*window;
	t_image		image;
}				t_info;



#endif