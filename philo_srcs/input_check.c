/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:21:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/18 16:26:21 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
