/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 13:22:17 by ashishae          #+#    #+#             */
/*   Updated: 2019/12/20 15:19:50 by ashishae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double ten_to(int pow)
{
	int i = 0;
	double result = 1;

	while (i < pow)
	{
		result /= 10;
		i++;
	}
	return (result);
}

double dot_part(char *str, int *len)
{
	int i;
	double result;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	result *= ten_to(i);
	*len += i;
	return (result);
}

double atod(char *str)
{
	double		nbr;
	double		sign;
	int			len;

	nbr = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
			|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		sign *= (*(str++) == '-' ? -1 : 1);
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *(str++) - '0';
	}
	if (*str == '.')
	{
		str++;
		nbr += dot_part(str, &len);
	}
	return (nbr * sign);
}

double atod_len(char *str, int *len)
{
	double		nbr;
	double		sign;
	int			i;

	nbr = 0;
	sign = 1;
	i = 0;

	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign *= (str[i++] == '-' ? -1 : 1);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		nbr += dot_part(&str[i], &i);
	}
	*len = i;
	return (nbr * sign);
}