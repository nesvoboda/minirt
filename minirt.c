/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:15:47 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/18 09:18:16 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void send_rays(void *mlx_ptr, void *window, t_list *objects, t_list *lights)
{
	int x;
	int y;
	t_ray sent;

	double t;
	x = 0;
	y = 0;
	while (y < IMG_HEIGHT)
	{
		x = 0;
		while (x < IMG_WIDTH)
		{
			sent = ray_to_pixel(x, y);
			//printf("Sent ray. Origin: x: %f y: %f z: %f. direction: x %f y %f z %f\n", sent.origin.x, sent.origin.y, sent.origin.z, sent.direction.x, sent.direction.y, sent.direction.z);
			mlx_pixel_put(mlx_ptr, window, x, y, get_color(objects, lights, sent));

			x++;
		}
		y++;
	}
	//mlx_ptr_put(id, window);
}

int main()
{
	void *id = mlx_init ();
	void *window = mlx_new_window (id, IMG_WIDTH, IMG_HEIGHT, "lol");
	t_list *objects;
	t_list *lights;
	t_object *this_object;

	lights = get_lights();
	objects = get_objects();
	//mlx_string_put(id, window, 20, 20, 0xfffafa, "Hello World!");

	send_rays(id, window, objects, lights);
	mlx_loop(id);
	return (0);
}
