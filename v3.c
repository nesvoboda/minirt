/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:17:58 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 18:51:25 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v3.h"
#include <math.h>

void	normalize_vector(t_v3 *vector)
{
	double len;

	len = sqrt(vector->x * vector->x + vector->y
	* vector->y + vector->z * vector->z);
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
	return (sqrt(vector.x * vector.x + vector.y * vector.y +
													vector.z * vector.z));
}

double	dot_product(t_v3 a, t_v3 b)
{
	double sum = 0;

	sum = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return sum;
}
