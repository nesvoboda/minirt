/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:15:47 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/21 19:44:13 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void make_pixel(t_image image, int x, int y, int color)
{
	char *dst;
	printf("Image addr: %p\n", image.addr);
	dst = image.addr + y * image.line_length + x * image.bits_per_pixel / 8;
	*(unsigned int *)dst = *(unsigned int *)color;
}

void send_rays(void *mlx_ptr, void *window, t_info *info)
{
	int x;
	int y;
	t_ray sent;

	double t;
	x = 0;
	y = 0;
	while (y < info->scene->height)
	{
		x = 0;
		while (x < info->scene->width)
		{
			sent = ray_to_pixel(x, y, info->scene);
			//printf("Sent ray. Origin: x: %f y: %f z: %f. direction: x %f y %f z %f\n", sent.origin.x, sent.origin.y, sent.origin.z, sent.direction.x, sent.direction.y, sent.direction.z);
			//mlx_pixel_put(mlx_ptr, window, x, y, get_color(scene, sent));
			info->image.addr[y * info->scene->width + x] = (unsigned int) get_color(info->scene, sent);
			// make_pixel(info->image, x, y, get_color(info->scene, sent));

			x++;
		}
		y++;
	}
	//mlx_ptr_put(id, window);
}

void	render(int camera_number, t_info *info)
{
	int cameras_available;


	cameras_available = ft_lstsize(info->scene->cameras);
	info->scene->selected_camera = camera_number % cameras_available;
	send_rays(info->id, info->window, info);
	mlx_put_image_to_window(info->id, info->window, info->image.img, 0, 0);
}

void	rerender(int key, t_info *info)
{
	if (key == 124)
		info->camera_number += 1;
	else if (key == 123)
		info->camera_number -= 1;
	if (!mlx_string_put(info->id, info->window, 10, 10, 0xffffff, "Rerendering. Please wait."))
		render(info->camera_number, info);
}



int main()
{
	t_info info;

	info.scene = parse_file("scene.rt");

	info.id = mlx_init();
	info.window = mlx_new_window (info.id, info.scene->width, info.scene->height, "miniRT");



	info.image.img = mlx_new_image(info.id, info.scene->width, info.scene->height);
	info.image.addr = mlx_get_data_addr(info.image.img,
										&(info.image.bits_per_pixel),
										&(info.image.line_length),
										&(info.image.endian));
	info.camera_number = 0;

	// t_list *runner;
	// t_light *light;
	// runner = scene->lights;
	// while (runner != NULL)
	// {
	// 	light = runner->content;
	// 	printf("light. | color: r: %f g: %f b: %f | p x: %f y: %f z: %f | intensity: %f\n", light->color.red,
	// 	light->color.green, light->color.blue, light->p0.x, light->p0.y, light->p0.z, light->intensity);
	// 	runner = runner->next;
	// }

	render(0, &info);
	mlx_key_hook (info.window, rerender, &info);

	mlx_loop(info.id);
	return (0);
}
