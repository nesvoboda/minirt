/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:55:36 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/15 13:21:28 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H
# include "bmp.h"
# include "color.h"
# include "stdlib.h"

t_pixel	**create_buffer(int height, int width);
void	free_buffer(t_pixel **buffer, int height, int width);
t_pixel	pix_from_int(int color);

#endif
