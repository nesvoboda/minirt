/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 09:55:10 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 11:41:16 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# include "v3.h"

typedef struct s_matrix
{
	double d[4][4];
}				t_matrix;

t_v3 multiply_by_matrix(t_v3 p, t_matrix m);
t_matrix lookAt(t_v3 origin, t_v3 cam_vector);

#endif