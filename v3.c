/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:17:58 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/07 10:35:42 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v3.h"
#include <math.h>

void	normalize_vector2(t_v3 *vector)
{
	double len;

	len = vector_len(*vector);
	vector->x /= len;
	vector->y /= len;
	vector->z /= len;
}

void	normalize_vector(t_v3 *vector)
{
	double len;

	len = sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
	vector->x /= len;
	vector->y /= len;
	vector->z /= len;
}


t_v3	create_v3(double x, double y, double z)
{
	t_v3 result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

double	vector_len(t_v3 vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}

double dot_product(t_v3 a, t_v3 b)
{
        double sum = 0;

 		sum = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
        return sum;
}

t_v3	cross_product(t_v3 a, t_v3 b)
{
	t_v3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_v3	substract(t_v3 vec1, t_v3 vec2)
{
	t_v3 result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_v3	v3_add(t_v3 vec1, t_v3 vec2)
{
	t_v3 result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_v3	v3_multiply(t_v3 vec1, double x)
{
	t_v3 result;

	result.x = vec1.x * x;
	result.y = vec1.y * x;
	result.z = vec1.z * x;
	return (result);
}