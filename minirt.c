/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:15:47 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/03 21:31:31 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "v3.h"
#include "ray.h"
#include "list.h"
#include "color.h"
#include <stdlib.h>
#define IMG_HEIGHT 1000
#define IMG_WIDTH 1000
#define FOV 90

typedef enum object_type
{
	SPHERE,
	CUBE,
	PLANE,
	LIGHT
}		otype;

typedef struct	s_sphere
{
	t_v3 center;
	double radius;
}				t_sphere;

typedef struct s_light
{
	t_v3 p0;
	double intensity;
	int color;
}				t_light;

typedef struct s_plane
{
	t_v3 p0;
	t_v3 normal;
}				t_plane;

typedef struct	s_object
{
	otype	type;
	void *ptr;
	int color;
	double	albedo;

}				t_object;

t_ray	ray_to_pixel(int x, int y)
{
	double aspect_ratio;
	double p_x;
	double p_y;
	t_ray result;
	t_v3	direction;

	aspect_ratio = (double)IMG_WIDTH / (double)IMG_HEIGHT;
	p_x = (2 * (x + 0.5) / (double)IMG_WIDTH - 1) * aspect_ratio;
	p_y = (1 - 2 * (y + 0.5) / (double)IMG_HEIGHT); // * tan(FOV / 2 * M_PI / 180);
	direction = create_v3(p_x, p_y, -1);
	normalize_vector(&direction);
	result = create_ray(create_v3(0, 0, 0), direction);
	return (result);
}


void	swap_doubles(double *a, double *b)
{
	double buffer;
	buffer = *a;
	*a = *b;
	*b = buffer;
}

int solveQuadratic(double a, double b, double c, double *x0, double *x1)
{
    double discr = b * b - 4.0 * a * c;
    if (discr < 0)
    	return (0);
    else if (discr == 0)
    {
    	*x0 = *x1 = -0.5 * b / a;
    }
    else
    {
        double q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
        *x0 = q / a;
        *x1 = c / q;
    }
	if (*x0 > *x1)
		swap_doubles(x0, x1);

    return (1);
}



int	intersect_sphere(t_ray ray, t_sphere sphere, double *t)
{
		double tca;
		double d2;
		double thc;
		double t0;
		double t1;
		//	geometric solution
		// t_v3 l = substract(sphere.center, ray.origin);
		// tca = dot_product(l, ray.direction);
		// if (tca < 0)
		// {
		// 	return (0);
		// }

		// d2 = dot_product(l, l) - tca * tca;
		// if (d2 > sphere.radius * sphere.radius)
		// {
		// 	return (0);
		// }
		// thc = sqrt(sphere.radius * sphere.radius - d2);
		// t0 = tca - thc;
		// t1 = tca + thc;

		// // analytic solution

		t_v3 l = substract(ray.origin, sphere.center);
		double a = dot_product(ray.direction, ray.direction);
		double b = 2.0 * dot_product(ray.direction, l);
		double c = dot_product(l, l) - (sphere.radius * sphere.radius);
		if (!solveQuadratic(a, b, c, &t0, &t1))
			return 0;

		if (t0 < 0) {
			t0 = t1; // if t0 is negative, let's use t1 instead
			if (t0 < 0)
				return (0); // both t0 and t1 are negative
		}
		*t = t0;
		return (1);
}

int intersect_plane(t_ray ray, t_plane plane, double *t)
{
	double denom = dot_product(plane.normal, ray.direction);
	if (denom > 1e-6)
	{
		t_v3 p0l0 = substract(plane.p0, ray.origin);
		*t = dot_product(p0l0, plane.normal) / denom;
		return (t >= 0);
	}
	return (0);
}

int		intersect(t_ray sent, t_object *object, double *t)
{
	if (object->type == SPHERE)
		return (intersect_sphere(sent, *(t_sphere *)object->ptr, t));
	else if (object->type == PLANE)
		return (intersect_plane(sent, *(t_plane *)object->ptr, t));
}

t_v3	get_sphere_normal(t_v3 point, t_sphere sphere)
{
	t_v3 n = substract(point, sphere.center);
	normalize_vector(&n);
	return (n);
}

t_v3	get_plane_normal(t_plane plane)
{
	t_v3 ret;
	ret = plane.normal;
	normalize_vector(&ret);
	return (ret);
}

t_v3	get_normal(t_v3 point, t_object *object)
{
	if (object->type == SPHERE)
		return (get_sphere_normal(point, *(t_sphere *)object->ptr));
	if (object->type == SPHERE)
		return (get_plane_normal(*(t_plane *)object->ptr));
}

int		intersect_with_all(t_list *objects, t_ray sent, t_object **closest_object, double *t_min)
{
	t_list		*runner;
	t_object	*this_object;
	double		t;

	*closest_object = NULL;
	runner = objects;
	*t_min = HUGE_VAL;
	while (runner != NULL)
	{
		this_object = runner->content;
		if (intersect(sent, this_object, &t))
		{
			if (t < *t_min)
			{
				*closest_object = this_object;
				*t_min = t;
			}
		}
		runner = runner->next;
	}
	if (*closest_object != NULL)
	{
		return (1);
	}
	else
		return (0);
}

int		get_color(t_list *objects, t_ray sent)
{

	double t_min;

	t_object *closest_object;
	t_object *closest_object2;

	t_v3	hit_point;
	t_v3	hit_normal;
	double  coeff = 0;
	t_light	light;
	t_v3 light_vector;
	t_v3 light_ray;
	t_ray lray;

	light.p0 = create_v3(-7, 0, 0);
	light.intensity = 0.7;
	light.color = 0xffffff;

	if (intersect_with_all(objects, sent, &closest_object, &t_min))
	{
				//printf("t %f\n", t_min);
		hit_point = v3_add(sent.origin, v3_multiply(sent.direction, t_min));
		//printf("hit_point x: %f y: %f z: %f\n", hit_point.x, hit_point.y, hit_point.z);
		//sleep(1);
		hit_normal = get_normal(hit_point, closest_object);
		// normalize_vector(&hit_normal);
		light_vector = substract(light.p0, hit_point);
		// normalize_vector(&light_vector);
		light_ray = substract(light.p0, hit_point);
		//normalize_vector(&light_ray);
		lray = create_ray(v3_add(hit_point, v3_multiply(hit_normal, 0.001)), light_ray);
		if (!intersect_with_all(objects, lray, &closest_object2, &t_min) || t_min < 0)
		{
			coeff = fmax(0, dot_product(hit_normal, light_vector));
			coeff *= closest_object->albedo / M_PI * light.intensity;
		}
		coeff += 0.2;
		printf("coeff %f\n", coeff);
		return (color_coefficient(closest_object->color, fmin(coeff, 0.99)));
		// return (0xff);
	}
	else
		return (0);
}

void send_rays(void *mlx_ptr, void *window, t_list *objects)
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
			mlx_pixel_put(mlx_ptr, window, x, y, get_color(objects, sent));

			x++;
		}
		y++;
	}
	//mlx_ptr_put(id, window);
}

t_sphere 	*new_sphere(t_v3 center, double radius)
{
	t_sphere *sphere;
	sphere = malloc(sizeof(t_sphere));
	sphere->center = center;
	sphere->radius = radius;
	return (sphere);
}

t_plane 	*new_plane(t_v3 p0, t_v3 normal)
{
	t_plane *plane;
	plane = malloc(sizeof(t_plane));
	plane->p0 = p0;
	plane->normal = normal;
	return (plane);
}

t_object	*new_object(otype type, void *ptr, int color)
{
	t_object *result;
	result = malloc(sizeof(t_object));
	result->type = type;
	result->ptr = ptr;
	result->color = color;
	result->albedo = 0.3;
	return (result);
}

t_list		*get_objects()
{
	t_list *result;
	t_object *object;
	object = new_object(SPHERE,
		new_sphere(create_v3(0, 0, -8), 2), 0xff);
	ft_lstadd_back(&result, ft_lstnew(object));
	object = new_object(SPHERE,
		new_sphere(create_v3(-2, 0, -5), 0.5), 0xff0000);
	ft_lstadd_back(&result, ft_lstnew(object));
	// object = new_object(SPHERE,
	// 	new_sphere(create_v3(-7, 5, -20), 2), 0xFF0000);
	// ft_lstadd_back(&result, ft_lstnew(object));
	// object = new_object(SPHERE,
	// 	new_sphere(create_v3(3, 5, -10), 2), 0xFF0F00);
	// ft_lstadd_back(&result, ft_lstnew(object));
	t_v3 plane_vector = create_v3(0, 300, -100);
	normalize_vector(&plane_vector);
	object = new_object(PLANE,
		new_plane(create_v3(0, 0, -7), plane_vector), 0xffa500);
	ft_lstadd_back(&result, ft_lstnew(object));
	return (result);
}

int main()
{
	void *id = mlx_init ();
	void *window = mlx_new_window (id, IMG_WIDTH, IMG_HEIGHT, "lol");
	t_list *objects;
	t_object *this_object;

	objects = get_objects();
	this_object = objects->content;
	printf("Yo! %d\n", this_object->color);
	//mlx_string_put(id, window, 20, 20, 0xfffafa, "Hello World!");

	send_rays(id, window, objects);
	mlx_loop(id);
	return (0);
}
