/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:27:06 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 14:55:28 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_len(const char *str, int *len);
double atod_len(char *str, int *len);
double atod(char *str);
t_scene *parse_file(char *path);