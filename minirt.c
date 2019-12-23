/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:15:47 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 17:15:33 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

pixel **create_buffer(int height, int width)
{
	pixel *line;
	pixel **result;
	int i;

	i = 0;
	result = malloc(sizeof(pixel *) * height);
	while (i < height)
	{
		result[i] = malloc(sizeof(pixel) * width);
		i++;
	}
	return (result);
}

void free_buffer(pixel **buffer, int height, int width)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}

pixel	pix_from_int(int color)
{
	t_color tc;
	pixel result;

	tc = int_to_color(color);

	result.B = tc.blue;
	result.G = tc.green;
	result.R = tc.red;
	return (result);
}

void send_rays(void *mlx_ptr, void *window, t_info *info, int save)
{
	int x;
	int y;
	int color;
	pixel **buffer;

	x = 0;
	y = 0;
	buffer = create_buffer(info->scene->height, info->scene->width);
	while (y < info->scene->height)
	{
		x = 0;
		while (x < info->scene->width)
		{
			color = get_color(info->scene, ray_to_pixel(x, y, info->scene));
			if (save)
				buffer[y][x] = pix_from_int(color);
			else
				info->image.addr[y * info->scene->width + x] = color;
			x++;
		}
		y++;
	}
	if (save)
		writeBMP("file.bmp", info->scene->width, info->scene->height, buffer);
	free_buffer(buffer, info->scene->height, info->scene->width);
}

void	render(int camera_number, t_info *info, int save)
{
	int cameras_available;

	cameras_available = ft_lstsize(info->scene->cameras);
	info->scene->selected_camera = camera_number % cameras_available;
	send_rays(info->id, info->window, info, save);
	if (save == 0)
		mlx_put_image_to_window(info->id, info->window, info->image.img, 0, 0);
}

void	rerender(int key, t_info *info)
{
	if (key == 124)
		info->camera_number += 1;
	else if (key == 123)
		info->camera_number -= 1;
	else if (key == 53)
		exit(0);

	render(info->camera_number, info, 0);
}

int w_close(t_info *info)
{
	printf("Close triggered\n");
	mlx_destroy_window(info->id, info->window);
	exit(0);
}

void minirt(char *filename, int save)
{
	t_info info;

	info.scene = parse_file(filename);
	info.camera_number = 0;

	if (save == 1)
	{
		render (0, &info, 1);
		return ;
	}

	info.id = mlx_init();
	info.window = mlx_new_window (info.id, info.scene->width, info.scene->height, "miniRT");
	info.image.img = mlx_new_image(info.id, info.scene->width, info.scene->height);
	info.image.addr = mlx_get_data_addr(info.image.img,
										&(info.image.bits_per_pixel),
										&(info.image.line_length),
										&(info.image.endian));
	mlx_hook(info.window, 17, 0, w_close, &info);
	mlx_key_hook (info.window, rerender, &info);

	render(0, &info, save);

	mlx_loop(info.id);
}

int main(int ac, char **av)
{
	if (ac < 2 || ac > 3)
		return (42);
	else
	{
		if (ac == 2)
			minirt(av[1], 0);
		else if (ft_strncmp(av[2], "--save", ft_strlen(av[2])) == 0)
			minirt(av[1], 1);
	}
	return (0);
}
