/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:09:58 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 19:10:55 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H
# include "v3.h"
# include "ray.h"

typedef struct	s_square
{
	t_v3 center;
	t_v3 normal;
	double length;
}				t_square;

t_square		*new_square(t_v3 center, t_v3 normal, double length);
t_v3			get_square_normal(t_square square);
int				intersect_square(t_ray ray, t_square square, double *t);

#endif