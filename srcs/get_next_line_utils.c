/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:24:37 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/17 18:57:05 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*resize(t_memory *memory)
{
	char	*result;
	int		i;
	int		y;
	int		current_length;

	current_length = ft_strlen(memory->str) - memory->position;
	memory->length = current_length;
	if (!(result = malloc(sizeof(char) * (BUFFER_SIZE + current_length + 1))))
		return (NULL);
	i = memory->position;
	y = 0;
	while (memory->str[i])
		result[y++] = memory->str[i++];
	result[y] = '\0';
	free(memory->str);
	memory->str = result;
	memory->position = 0;
	return (result);
}

int		find_nl(t_memory memory)
{
	int		i;
	char	*str;

	str = &memory.str[memory.position];
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
