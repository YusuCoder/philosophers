/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:21:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/14 17:12:58 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	error_msg(char *msg, int return_value)
{
	printf("%s", msg);
	return (return_value);
}

static int	ft_atoi(char *str)
{
	unsigned long long int	num;
	int						i;

	i = 0;
	num = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	valid_input(int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	while (i < argc)
	{
		if (is_digit(argv[i]))
			return (1);
		num = ft_atoi(argv[i]);
		if (i == 1 && (num <= 0 || num > 250))
			return (1);
		if (i != 1 && num == -1)
			return (1);
		i++;
	}
	return (0);
}
