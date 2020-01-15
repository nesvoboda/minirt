/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 11:00:42 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/15 13:24:01 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# define PIXEL_DATA_OFFSET 54
# define HEADER_SIZE 40
# define PLANES 1
# define BITS_PER_PIXEL 24

typedef struct	s_pixel{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}				t_pixel;

int				write_bmp(char *filename, unsigned int width,
							unsigned int height, t_pixel **pixels);

#endif
