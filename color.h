/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:48:15 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/21 19:28:18 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
#define COLOR_H

typedef struct 	s_color
{
	int red;
	int green;
	int blue;
}				t_color;
t_color			int_to_color(int color);
int				color_to_int(t_color color);
int				color_coefficient(int int_color, double coefficient);
int				color_concat(int c1, int c2);
int				color_add(int int_color, double add);
int				color_to_int2(t_color color);

#endif