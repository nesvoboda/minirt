/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:18:41 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/03 15:27:25 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3_H
# define V3_H

/*
**	Basic functions to work in 3d (and width vectors)
*/

typedef struct	s_v3
{
	double x;
	double y;
	double z;
}				t_v3;
t_v3	create_v3(double x, double y, double z);
double	vector_len(t_v3 vector);
double	dot_product(t_v3 a, t_v3 b);
t_v3	substract(t_v3 vec1, t_v3 vec2);
void	normalize_vector(t_v3 *vector);
t_v3	v3_add(t_v3 vec1, t_v3 vec2);
t_v3	v3_multiply(t_v3 vec1, double x);

#endif