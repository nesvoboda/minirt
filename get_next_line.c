/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 13:57:26 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 12:48:05 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_to_mem(t_memory *memory, int fd)
{
	int			received;
	char		*resized;

	resized = "start";
	if (memory->str == NULL || memory->fd != fd)
	{
		memory->position = 0;
		memory->length = 0;
		if ((memory->str = malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
			return (-1);
	}
	else
		resized = resize(memory);
	memory->fd = fd;
	if ((received = read(fd, memory->str + memory->length, BUFFER_SIZE)) == -1
			|| !resized)
	{
		free(memory->str);
		memory->str = NULL;
		return (-1);
	}
	(memory->str)[memory->length + received] = '\0';
	return (received);
}

int		copy_to_line(t_memory *memory, char **line)
{
	int i;
	int line_size;

	if (find_nl(*memory) == -1)
		line_size = ft_strlen(&(memory->str[memory->position]));
	else
		line_size = find_nl(*memory);
	if ((*line = malloc(sizeof(char) * (line_size + 1))) == NULL)
		return (-1);
	i = 0;
	while (i < line_size)
		(*line)[i++] = memory->str[memory->position++];
	memory->position++;
	(*line)[i] = '\0';
	return (line_size);
}

int		get_next_line(int fd, char **line)
{
	int				received;
	static t_memory	memory;
	int				line_size;

	if (!line || BUFFER_SIZE == 0 || fd < 0)
		return (-1);
	if ((received = read_to_mem(&memory, fd)) == -1)
		return (-1);
	while (received >= BUFFER_SIZE && (find_nl(memory) == -1))
		if ((received = read_to_mem(&memory, fd)) == -1)
			return (-1);
	if ((line_size = copy_to_line(&memory, line)) == -1)
		return (-1);
	if (received < BUFFER_SIZE && line_size >= ft_strlen(memory.str))
	{
		free(memory.str);
		memory.str = NULL;
		return (0);
	}
	else if (received == -1)
		return (-1);
	else
		return (1);
}