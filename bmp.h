/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 11:00:42 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/23 11:23:47 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

typedef struct {
	unsigned char B;
	unsigned char G;
	unsigned char R;
} pixel;

int writeBMP(char* filename, unsigned int width, unsigned int height, pixel** pixels);

#endif