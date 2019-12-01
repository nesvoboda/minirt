/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:15:47 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/01 09:28:26 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#define IMG_HEIGHT 1200
#define IMG_WIDTH 1600
#define FOV 90

typedef struct	s_sphere
{
	t_v3 center;
	double radius;
}				t_sphere;

int solveQuadratic(double a, double b, double c, double *x0, double *x1) 
{ 
    double discr = b * b - 4.0 * a * c;
    double buffer;
    if (discr < 0)
    	return (0); 
    else if (discr == 0)
    {
    	*x0 = *x1 = - 0.5 * b / a;
    }
    else
    { 
        double q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr)); 
        *x0 = q / a;
        *x1 = c / q;
    } 
    if (*x0 > *x1)
    {
    	buffer = *x1;
    	*x1 = *x0;
    	*x0 = buffer;
    }
    return (1); 
}

void	swap_doubles(double *a, double *b)
{
	double buffer;
	buffer = *a;
	*a = *b;
	*b = buffer;
}

int	intersect_sphere(t_ray ray, t_sphere sphere)
{
		double tca;
		double d2;
		double thc;
		double t0;
		double t1;
		double buffer;
		//	geometric solution
		t_v3 l = substract(sphere.center, ray.origin);
		tca = dot_product(l, ray.direction);
		if (tca < 0)
		{
			printf("Tca < 0");
			return (0);
		}

		d2 = dot_product(l, l) - tca * tca; 
		if (d2 > (sphere.radius * sphere.radius))
		{
			return (0); 
		}
		thc = sqrt(sphere.radius * sphere.radius - d2); 
		t0 = tca - thc; 
		t1 = tca + thc;

		// // analytic solution

		// t_v3 l = substract(ray.origin, sphere.center);
		// double a = dot_product(ray.direction, ray.direction);
		// double b = 2.0 * dot_product(ray.direction, l);
		// double c = dot_product(l, l) - pow(sphere.radius, 2.0);
		// if (!solveQuadratic(a, b, c, &t0, &t1))
		// 	return 0; 

		if (t0 > t1)
		swap_doubles(&t0, &t1);

		if (t0 < 0) { 
			t0 = t1; // if t0 is negative, let's use t1 instead 
			if (t0 < 0)
				return (0); // both t0 and t1 are negative 
		}
		//t = t0; 
		return (1); 
		}

void send_rays(void *mlx_ptr, void *window)
{
	int x;
	int y;
	t_ray sent;
	t_sphere sphere;

	sphere.center = create_v3(0, 4, -8);
	sphere.radius = 2;

	x = 0;
	y = 0;
	while (y < IMG_HEIGHT)
	{
		x = 0;
		while (x < IMG_WIDTH)
		{
			sent = ray_to_pixel(x, y);
			//printf("Sent ray. Origin: x: %f y: %f z: %f. direction: x %f y %f z %f\n", sent.origin.x, sent.origin.y, sent.origin.z, sent.direction.x, sent.direction.y, sent.direction.z);
			if (intersect_sphere(sent, sphere))
			{
				mlx_pixel_put(mlx_ptr, window, x, y, 0xfffafa);
			}
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
	//mlx_string_put(id, window, 20, 20, 0xfffafa, "Hello World!");
	send_rays(id, window);
	mlx_loop(id);
	return (0);
}
