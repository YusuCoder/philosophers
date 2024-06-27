/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:25:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/27 18:03:19 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	join_threads(t_ryusupov *data, pthread_t *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(philo[i], NULL) != 0)
		{
			printf("fail\n");
		}
		pthread_mutex_destroy(&data->mutexx[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_st);
	pthread_mutex_destroy(&data->mutex_death);
	ft_free_c_data(data);
	free(philo);
}

void	philo_status(t_ryusupov *philo, char c)
{
	int	i;

	pthread_mutex_lock(&philo->data->mutex_st);
	i = calc_timestamp(philo->data->begin);
	if (philo->data->end == 0)
	{
		if (c == 'f')
			printf(YELLOW "%d %d has taken a fork\n" RESET, i, philo->i_philo
				+ 1);
		else if (c == 'e')
			printf(GREEN "%d %d is eating\n" RESET, i, philo->i_philo + 1);
		else if (c == 's')
			printf(BLUE "%d %d is sleeping\n" RESET, i, philo->i_philo + 1);
		else if (c == 't')
			printf(CYAN "%d %d is thinking\n" RESET, i, philo->i_philo + 1);
		else if (c == 'd')
			printf(RED "%d %d died\n" RESET, i, philo->i_philo + 1);
	}
	pthread_mutex_unlock(&philo->data->mutex_st);
}

void	sleep_dead(t_ryusupov *philo)
{
	pthread_mutex_lock(&philo->data->mutex_death);
	philo_sleep(philo, philo->data->death_time);
	pthread_mutex_unlock(&philo->data->mutex_death);
	pthread_mutex_lock(&philo->data->mutex_st);
	philo_status(philo, 'd');
	pthread_mutex_unlock(&philo->data->mutex_st);
	free(philo);
}

void	*routine(void *argv)
{
	t_ryusupov	*philo;

	philo = argv;
	wait_for_start(philo);
	gettimeofday(&philo->t_food, NULL);
	if ((philo->i_philo + 1) % 2 != 0)
		usleep(100);
	pthread_mutex_lock(&philo->data->mutex_st);
	if (philo->data->philo_count > 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_st);
		routine_loop(philo);
		free(philo);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->mutex_st);
		sleep_dead(philo);
	}
	return (NULL);
}
