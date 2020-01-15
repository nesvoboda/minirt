/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_len.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 13:45:44 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/15 17:43:35 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ATOI_LEN_H
# define FT_ATOI_LEN_H

# include "unistd.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi_len(const char *str, int *len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
double	ten_to(int pow);
double	dot_part(char *str, int *len);
double	atod_len(char *str, int *len);

#endif
