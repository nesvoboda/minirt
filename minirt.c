/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:15:47 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 18:27:17 by ashishae         ###   ########.fr       */
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
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			sent = ray_to_pixel(x, y, scene);
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
	void *window;
	t_scene *scene;

	scene = parse_file("scene.rt");
	window = mlx_new_window (id, scene->width, scene->height, "miniRT");

	send_rays(id, window, scene);
	mlx_loop(id);
	return (0);
}
