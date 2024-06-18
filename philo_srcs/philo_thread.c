/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:25:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/18 19:32:13 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void	philo_status(t_ryusupov *philo, char c)
{
	int	i;

	i = calc_time(&philo->data->t_time);
	if (philo->data->end == 0)
	{
		pthread_mutex_lock(&philo->data->mutex_st);
		if (c == 'f')
			printf("%d %d has taken a fork\n", i, philo->i_philo + 1);
		else if (c == 'e')
			printf("%d %d is eating\n", i, philo->i_philo + 1);
		else if (c == 's')
			printf("%d %d is sleeping\n", i, philo->i_philo + 1);
		else if (c == 't')
			printf("%d %d is thinking\n", i, philo->i_philo + 1);
		else if (c == 'd')
			printf("%d %d died\n", i, philo->i_philo + 1);
		pthread_mutex_unlock(&philo->data->mutex_st);
	}
}

void	sleep_dead(t_ryusupov *philo)
{
		is_sleep(philo, philo->data->death_time);
		philo_status(philo, 'd');
		free_philo(philo);
}

void	*routine(void *argv)
{
	t_ryusupov	*philo;

	philo = argv;
	while (philo->data->t_time.tv_usec == 0)
		usleep(100);
	gettimeofday(&philo->data->t_time, NULL);
	gettimeofday(&philo->t_food, NULL);
	if ((philo->i_philo + 1) % 2 != 0)
		usleep(100);
	if (philo->data->philo_count > 1)
	{
		while (philo->data->end == 0)
		{
			philo_death(philo);
			if (philo->data->end == 0)
				think_eat_sleep(philo, philo->i_philo);
		}
		free_philo(philo);
	}
	else
		sleep_dead(philo);
	return (NULL);
}
