/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:15:47 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/09 15:02:55 by ashishae         ###   ########.fr       */
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
	LIGHT,
	TRIANGLE,
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

typedef struct s_triangle
{
	t_v3 a;
	t_v3 b;
	t_v3 c;

}				t_triangle;

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
		double t0;
		double t1;

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
	if (fabs(denom) > 1e-6)
	{
		t_v3 p0l0 = substract(plane.p0, ray.origin);
		*t = dot_product(p0l0, plane.normal) / denom;
		return (*t >= 0);
	}
	return (0);
}

int intersect_triangle(t_ray ray, t_triangle triangle, double *t)
{
	t_v3 A = substract(triangle.b, triangle.a);
	t_v3 B = substract(triangle.c, triangle.a);
	t_v3 N = cross_product(A, B);
	normalize_vector(&N);
	//double sign = -1;

	double angle = dot_product(N, ray.direction);
	if (fabs(angle) < 1e-6)
	{

		return (0);
	}

	double d = dot_product(N, triangle.a);

	*t = (dot_product(N, ray.origin) + d) / angle;

	if (*t < 0)
	{
		return (0);
	}
	t_v3 p = v3_add(ray.origin, v3_multiply(ray.direction, *t));

	t_v3 C;

	t_v3 edge0 = substract(triangle.b, triangle.a);
	t_v3 vp0 = substract(p, triangle.a);

	C = cross_product(edge0, vp0);

	if (dot_product(N, C) < 0)
		return (0);

	t_v3 edge1 = substract(triangle.c, triangle.b);
	t_v3 vp1 = substract(p, triangle.b);
	C = cross_product(edge1, vp1);

	if (dot_product(N, C) < 0)
		return (0);

	t_v3 edge2 = substract(triangle.a, triangle.c);
	t_v3 vp2 = substract(p, triangle.c);

	C = cross_product(edge2, vp2);

	if (dot_product(N, C) < 0)
		return (0);

	return (1);
}

int		intersect(t_ray sent, t_object *object, double *t)
{
	if (object->type == SPHERE)
		return (intersect_sphere(sent, *(t_sphere *)object->ptr, t));
	else if (object->type == PLANE)
		return (intersect_plane(sent, *(t_plane *)object->ptr, t));
	else if (object->type == TRIANGLE)
		return (intersect_triangle(sent, *(t_triangle *)object->ptr, t));
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
	//normalize_vector(&ret);
	//printf("%f %f %f\n", ret.x, ret.y, ret.z);
	return (ret);
}

t_v3	get_triangle_normal(t_triangle triangle)
{
	t_v3 A = substract(triangle.b, triangle.a);
	t_v3 B = substract(triangle.c, triangle.a);
	t_v3 N = cross_product(A, B);
	normalize_vector(&N);
	//printf("N: %f %f %f\n", N.x, N.y, N.z);
	return (N);
}

t_v3	get_normal(t_v3 point, t_object *object)
{
	if (object->type == SPHERE)
	{
		//printf("Entered sphere normal\n");
		return (get_sphere_normal(point, *(t_sphere *)object->ptr));
	}
	if (object->type == PLANE)
	{
		//printf("Entered\n");
		return (get_plane_normal(*(t_plane *)object->ptr));
	}
	if (object->type == TRIANGLE)
	{
		//printf("Entered triangle normal\n");
		return (get_triangle_normal(*(t_triangle *)object->ptr));
	}
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

double		light_contribution(t_light light, t_v3 hit_point, t_v3 hit_normal, t_list *objects, t_object *closest_object)
{
	t_object *closest_object2;
	double t;
	t_v3	light_vector;
	t_v3	light_ray;
	t_ray	lray;
	int color_result = 0;
	double  coeff = 0;

	light_vector = substract(light.p0, hit_point);
	light_ray = substract(light.p0, hit_point);


	lray = create_ray(v3_add(hit_point, v3_multiply(hit_normal, 0.00001)), light_ray);
	if (!intersect_with_all(objects, lray, &closest_object2, &t))
	{
		coeff = fmax(0, dot_product(hit_normal, light_vector));
		coeff *= closest_object->albedo / M_PI * light.intensity;
	}
	return (coeff);
}

double		shade(t_list *objects, t_list *lights, t_ray sent, t_object *closest_object, double t_min)
{
	t_v3	hit_point;
	t_v3	hit_normal;
	t_list *runner;
	double coeff = 0;

	hit_point = v3_add(sent.origin, v3_multiply(sent.direction, t_min));
	hit_normal = get_normal(hit_point, closest_object);
	runner = lights;
	while (runner != NULL)
	{
		coeff += light_contribution(*(t_light *)(runner->content), hit_point, hit_normal, objects, closest_object);
		runner = runner->next;
	}
	return (coeff);
}

int		get_color(t_list *objects, t_list *lights, t_ray sent)
{

	double t_min;

	t_object *closest_object;
	t_object *closest_object2;

	t_light	light;
	double coeff;
	int		amb_color = 0xff;
	double		amb_intensity = 0.1;
	int color_result = 0;

	if (intersect_with_all(objects, sent, &closest_object, &t_min))
	{

		coeff = shade(objects, lights, sent, closest_object, t_min);
		amb_color = color_coefficient(0xff, amb_intensity);
		amb_color = color_concat(closest_object->color, amb_color);
		color_result = color_coefficient(amb_color, fmin(0.99, coeff));
		double ambient_max = 0.90 - fmin(0.99, coeff);

		return (color_result);
	}
	else
		return (0);
}

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

t_light *new_light(int color, double intensity, t_v3 p0)
{
	t_light *light;

	light = malloc(sizeof(t_light));
	light->color = color;
	light->intensity = intensity;
	light->p0 = p0;
	return (light);
}

t_sphere 	*new_sphere(t_v3 center, double radius)
{
	t_sphere *sphere;
	sphere = malloc(sizeof(t_sphere));
	sphere->center = center;
	sphere->radius = radius;
	return (sphere);
}

t_triangle		*new_triangle(t_v3 a, t_v3 b, t_v3 c)
{
	t_triangle *triangle;
	triangle = malloc(sizeof(t_triangle));
	triangle->a = a;
	triangle->b = b;
	triangle->c = c;
	return (triangle);
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
	result->albedo = 0.4;
	return (result);
}

t_list		*get_objects()
{
	t_list *result = NULL;
	t_object *object;
	// object = new_object(SPHERE,
	// 	new_sphere(create_v3(0, 0, -8), 2), 0xff);
	// ft_lstadd_back(&result, ft_lstnew(object));
	object = new_object(SPHERE,
		new_sphere(create_v3(-2, -1, -5), 0.5), 0xff0000);
	ft_lstadd_back(&result, ft_lstnew(object));

		object = new_object(SPHERE,
		new_sphere(create_v3(0, -2, -4), 0.5), 0xff0000);
	ft_lstadd_back(&result, ft_lstnew(object));
	// object = new_object(SPHERE,
	// 	new_sphere(create_v3(-7, 5, -20), 2), 0xFF0000);
	// ft_lstadd_back(&result, ft_lstnew(object));
	// object = new_object(SPHERE,
	// 	new_sphere(create_v3(3, 5, -10), 2), 0xFF0F00);
	// ft_lstadd_back(&result, ft_lstnew(object));
	t_v3 plane_vector = create_v3(0, 1, 0);
	normalize_vector(&plane_vector);
	printf("Plane vector is %f %f %f\n", plane_vector.x, plane_vector.y, plane_vector.z);
	object = new_object(PLANE,
		new_plane(create_v3(0, -3, -10), plane_vector), 0xffa500);
	ft_lstadd_back(&result, ft_lstnew(object));
	// object = new_object(TRIANGLE, new_triangle(create_v3(0,-1,-3), create_v3(2,-1, -5), create_v3(-2,-1,-5)), 0xff);
	// ft_lstadd_back(&result, ft_lstnew(object));
	return (result);
}

t_list		*get_lights()
{
	t_list *result = NULL;
	t_light *light;

	light = new_light(0xffffff, 0.5, create_v3(-5, 5, -4));
	ft_lstadd_back(&result, ft_lstnew(light));
	light = new_light(0xffffff, 0.5, create_v3(5, 5, -4));
	ft_lstadd_back(&result, ft_lstnew(light));
	return (result);
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
	t_list *runner = objects;
	while (runner != NULL)
	{
		this_object = runner->content;
		printf("Object type is %d\n", this_object->type == PLANE);
		runner = runner->next;
	}
	this_object = objects->content;
	printf("Yo! %d\n", this_object->color);
	//mlx_string_put(id, window, 20, 20, 0xfffafa, "Hello World!");

	send_rays(id, window, objects, lights);
	mlx_loop(id);
	return (0);
}
