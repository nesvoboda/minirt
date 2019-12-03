/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:48:15 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/03 16:04:30 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct 	s_color
{
	int red;
	int green;
	int blue;
}				t_color;
t_color int_to_color(int color);
int color_to_int(t_color color);
int	color_coefficient(int int_color, double coefficient);