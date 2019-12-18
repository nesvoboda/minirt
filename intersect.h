/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:40:37 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/17 13:52:41 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

int		intersect(t_ray sent, t_object *object, double *t);
int		intersect_with_all(t_list *objects, t_ray sent,
							t_object **closest_object, double *t_min);

#endif