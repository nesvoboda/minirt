/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:17:58 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/01 09:43:38 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v3.h"

void	normalize_vector(t_v3 *vector)
{
	double len;

	len = vector_len(*vector);
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
	vector.x *= vector.x;
	vector.y *= vector.y;
	vector.z *= vector.z;
	return (sqrt(vector.x + vector.y + vector.z));
}

double dot_product(t_v3 a, t_v3 b)
{
        double sum = 0;
        
 		sum += (a.x * b.x);
		sum += (a.y * b.y);
		sum += (a.z * b.z);
        return sum;
}

t_v3	substract(t_v3 vec1, t_v3 vec2)
{
	t_v3 result;

	result.z = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}