/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 19:25:29 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 19:28:05 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRATIC_H
# define QUADRATIC_H

typedef struct	s_qparams
{
	double	a;
	double	b;
	double	c;
}				t_qparams;
void			swap_doubles(double *a, double *b);
t_qparams		new_qparams(double a, double b, double c);
int				solve_quadratic(t_qparams params, double *x0, double *x1);

#endif