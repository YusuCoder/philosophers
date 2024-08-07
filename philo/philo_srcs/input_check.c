/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:21:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/31 16:03:51 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_free_c_data(t_ryusupov *c_data)
{
	free(c_data->mutexx);
	free(c_data->forks);
}

void	put_death(t_ryusupov *philo)
{
	int	timestamp;

	pthread_mutex_lock(&philo->data->mutex_st);
	timestamp = calc_timestamp(philo->data->begin);
	if (philo->is_locked == 0)
	{
		printf(RED "%d %d died\n" RESET, timestamp, philo->i_philo + 1);
		philo->is_locked = 1;
	}
	pthread_mutex_unlock(&philo->data->mutex_st);
	usleep(1000);
}

int	valid_input(int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '\0')
			return (1);
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
