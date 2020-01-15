/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:24:07 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/15 13:24:24 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "bmp.h"

/*
**	Ft_memset() is used to fill the future header with zeroes.
*/

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	*lim;

	str = b;
	lim = b + len;
	while (str != lim)
		*(str++) = (unsigned char)c;
	return (b);
}

/*
** fill_header() fills the header array with values that don't depend on the
** actual image.
**
** The settings are as follows:
** (byte)			(field name)		(set to)
**
** 0 and 1			FileType			magic bytes (B, M)
** 10				PixelDataOffset		54
** 14				HeaderSize			40
** 26				Planes				1
** 28				BitsPerPixel		24
**
** You can find the detailed explanation of the BMP format here:
** https://vee.gg/JEajJ
** (an article on itnext.io)
*/

void	fill_header(unsigned char *header)
{
	ft_memset(header, 0, 54);
	header[0] = 'B';
	header[1] = 'M';
	header[10] = PIXEL_DATA_OFFSET;
	header[14] = HEADER_SIZE;
	header[26] = PLANES;
	header[28] = BITS_PER_PIXEL;
}

/*
** Fill_sizes() fills the height, width, and filesize entries of the
** BMP header
*/

void	fill_sizes(unsigned char *header, unsigned int height,
					unsigned int width)
{
	unsigned int pixels_in_row;
	unsigned int padding_in_row;

	*(unsigned int *)(&header[18]) = width;
	*(unsigned int *)(&header[22]) = height;
	pixels_in_row = width * sizeof(t_pixel);
	padding_in_row = (4 - (pixels_in_row % 4)) % 4;
	header[2] = 54 + (pixels_in_row + padding_in_row) * height;
}

/*
** write_file() writes the pixel and padding bytes to the file
*/

void	write_file(unsigned int height, unsigned int width, t_pixel **pixels,
					int fd)
{
	unsigned int	pixels_in_row;
	unsigned int	padding_in_row;
	unsigned char	zeroes[3];
	int				row;

	zeroes[0] = 0;
	zeroes[1] = 0;
	zeroes[2] = 0;
	pixels_in_row = width * sizeof(t_pixel);
	padding_in_row = (4 - (pixels_in_row % 4)) % 4;
	row = height;
	while (row >= 0)
	{
		write(fd, pixels[row], pixels_in_row);
		write(fd, zeroes, padding_in_row);
		row--;
	}
}

/*
**	write_bmp() writes a pixel array to a file (called filename).
**	height and width must be specified.
*/

int		write_bmp(char *filename, unsigned int width, unsigned int height,
					t_pixel **pixels)
{
	int				fd;
	unsigned char	header[54];

	fill_header(header);
	fill_sizes(header, height, width);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
	write(fd, header, 54);
	write_file(height, width, pixels, fd);
	close(fd);
	return (0);
}
