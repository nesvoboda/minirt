/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:48:15 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/14 15:52:06 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "math.h"

typedef struct	s_color
{
	int red;
	int green;
	int blue;
}				t_color;

typedef union	u_int_color
{
	int				integer;
	unsigned char	comps[4];
}				t_int_color;

t_color			int_to_color(int color);
int				color_to_int(t_color color);

#endif
