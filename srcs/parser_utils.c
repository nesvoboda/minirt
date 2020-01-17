/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 18:34:29 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/17 18:58:18 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	handle_error(char *errormsg)
{
	write(2, "Error\n", 6);
	write(2, errormsg, ft_strlen(errormsg));
	write(2, "\n", 1);
	exit(-1);
}

int		open_file(char *path)
{
	int			fd;
	extern int	errno;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error(strerror(errno));
	return (fd);
}

int		line_fields(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i])
		i++;
	return (i);
}
