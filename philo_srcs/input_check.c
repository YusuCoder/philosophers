/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:21:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/25 14:00:18 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_free_c_data(t_ryusupov *c_data)
{
	free(c_data->mutexx);
	free(c_data->forks);
}

int	calc_timestamp(struct timeval start)
{
	struct timeval	now;
	long			seconds;
	long			microseconds;
	int				result;

	gettimeofday(&now, NULL);
	seconds = now.tv_sec - start.tv_sec;
	microseconds = now.tv_usec - start.tv_usec;
	result = (seconds * 1000) + (microseconds / 1000);
	return (result);
}

// int	calc_timestamp(struct timeval start)
// {
// 	int				result;
// 	struct timeval	now;

// 	gettimeofday(&now, NULL);
// 	result = (now.tv_sec * 1000) + (now.tv_usec / 1000);
// 	result -= (start.tv_sec * 1000) + (start.tv_usec / 1000);
// 	return (result);
// }

void	put_death(t_ryusupov *philo)
{
	int	timestamp;

	timestamp = calc_timestamp(philo->data->begin);
	pthread_mutex_lock(&philo->data->mutex_st);
	printf(RED "%d %d died\n" RESET, timestamp, philo->i_philo + 1);
	pthread_mutex_unlock(&philo->data->mutex_st);
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
