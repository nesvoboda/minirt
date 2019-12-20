/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:15:47 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 12:24:37 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void send_rays(void *mlx_ptr, void *window, t_scene *scene)
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
			mlx_pixel_put(mlx_ptr, window, x, y, get_color(scene, sent));

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
	t_scene *scene;

	scene = get_scene();

	//mlx_string_put(id, window, 20, 20, 0xfffafa, "Hello World!");

	send_rays(id, window, scene);
	mlx_loop(id);
	return (0);
}
