/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:01:25 by ashishae          #+#    #+#             */
/*   Updated: 2020/01/14 16:03:23 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	if (ac < 2 || ac > 3)
		return (42);
	else
	{
		if (ac == 2)
			minirt(av[1], 0);
		else if (ft_strncmp(av[2], "--save", ft_strlen(av[2])) == 0)
			minirt(av[1], 1);
	}
	return (0);
}
