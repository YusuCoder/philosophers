/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:25:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/22 00:07:19 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	join_threads (t_ryusupov *data, pthread_t *philo)
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
	free(data);
	free(philo);
}

void	philo_status(t_ryusupov *philo, char c)
{
	int	i;

	i = calc_timestamp(philo->data->begin);
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

void	ft_multiple_philos(t_ryusupov *philo)
{
	while (philo->data->end == 0)
	{
		philo_death(philo);
		if (philo->data->end == 0)
			think_eat_sleep(philo, philo->i_philo);
	}
	ft_free_philo(philo);
}

void	*routine(void *vargp)
{
	t_ryusupov	*philo_cpy;

	philo_cpy = vargp;
	while (philo_cpy->data->begin.tv_usec == 0)
		usleep(100);
	gettimeofday(&philo_cpy->data->begin, NULL);
	gettimeofday(&philo_cpy->t_food, NULL);
	if ((philo_cpy->i_philo + 1) % 2 != 0)
		usleep(100);
	if (philo_cpy->data->philo_count > 1)
		ft_multiple_philos(philo_cpy);
	else
	{
		philo_sleep(philo_cpy, philo_cpy->data->death_time);
		put_death(philo_cpy);
		ft_free_philo(philo_cpy);
	}
	return (NULL);
}

// void	sleep_dead(t_ryusupov *philo)
// {
// 		philo_sleep(philo, philo->data->death_time);
// 		put_death(philo);
// 		ft_free_philo(philo);
// }

// void	*routine(void *argv)
// {
// 	t_ryusupov	*philo;

// 	philo = argv;
// 	while (philo->data->begin.tv_usec == 0)
// 		usleep(100);
// 	gettimeofday(&philo->data->begin, NULL);
// 	gettimeofday(&philo->t_food, NULL);
// 	if ((philo->i_philo + 1) % 2 != 0)
// 		usleep(100);
// 	if (philo->data->philo_count > 1)
// 	{
// 		while (philo->data->end == 0)
// 		{
// 			philo_death(philo);
// 			if (philo->data->end == 0)
// 				think_eat_sleep(philo, philo->i_philo);
// 		}
// 		ft_free_philo(philo);
// 	}
// 	else
// 		sleep_dead(philo);
// 	return (NULL);
// }
