/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 13:57:23 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 15:06:24 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "stdlib.h"
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef	struct	s_memory
{
	char	*str;
	int		position;
	int		length;
	int		last_received;
	int		fd;
}				t_memory;
int				get_next_line(int fd, char **line);
int				ft_strlen(char *str);
char			*resize(t_memory *memory);
int				find_nl(t_memory memory);

#endif
