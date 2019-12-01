/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 09:25:57 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/01 09:46:08 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "v3.h"

typedef struct	s_ray
{
	t_v3 origin;
	t_v3 direction;
}				t_ray;
t_ray	create_ray(t_v3 origin, t_v3 direction);

#endif