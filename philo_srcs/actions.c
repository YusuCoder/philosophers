/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:28:09 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/27 18:10:02 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_death(t_ryusupov *philo)
{
	pthread_mutex_lock(&philo->data->mutex_death);
	pthread_mutex_lock(&philo->data->mutex_st);
	if (philo->data->end == 0)
	{
		if (calc_time(the_time(), philo->t_food) > philo->data->death_time)
		{
			philo_status(philo, 'd');
			philo->data->end = 1;
		}
		if (philo->data->completed_eating == philo->data->philo_count)
		{
			philo->data->end = 1;
		}
	}
	pthread_mutex_unlock(&philo->data->mutex_death);
	pthread_mutex_unlock(&philo->data->mutex_st);
}

void	philo_sleep(t_ryusupov *philo, int i)
{
	struct timeval	time;
	struct timeval	now;
	int				res;

	gettimeofday(&time, NULL);
	res = calc_time(time, philo->data->begin);
	res += i;
	gettimeofday(&now, NULL);
	while (calc_time(now, philo->data->begin) < res)
	{
		philo_death(philo);
		usleep(100);
		gettimeofday(&now, NULL);
	}
}

void	philo_eat(t_ryusupov *philo, int *right_fork, int *left_fork, int i)
{
	t_fork_info	fork_info;

	fork_info.left_index = get_index(philo, i - 1);
	fork_info.right_index = i;
	fork_info.left_fork = left_fork;
	fork_info.right_fork = right_fork;
	if (fork_info.left_index < fork_info.right_index)
	{
		philo_take_forks_left_first(philo, &fork_info);
	}
	else
		philo_take_forks_right_first(philo, &fork_info);
	gettimeofday(&philo->t_food, NULL);
	pthread_mutex_lock(&philo->data->mutex_st);
	philo->food++;
	if (philo->food == philo->data->eat_count)
		philo->data->completed_eating++;
	pthread_mutex_unlock(&philo->data->mutex_st);
	philo_status(philo, 'e');
	philo_sleep(philo, philo->data->eat_time);
	pthread_mutex_lock(&philo->data->mutexx[fork_info.left_index]);
	*(fork_info.left_fork) = 1;
	pthread_mutex_unlock(&philo->data->mutexx[fork_info.left_index]);
	pthread_mutex_lock(&philo->data->mutexx[fork_info.right_index]);
	*(fork_info.right_fork) = 1;
	pthread_mutex_unlock(&philo->data->mutexx[fork_info.right_index]);
}

void	think_eat_sleep(t_ryusupov *philo, int i)
{
	int	*rigth_fork;
	int	*left_fork;

	rigth_fork = &philo->data->forks[philo->i_philo];
	left_fork = &philo->data->forks[get_index(philo, philo->i_philo - 1)];
	philo_death(philo);
	if (*left_fork == 1)
	{
		philo_eat(philo, rigth_fork, left_fork, i);
		philo_status(philo, 's');
		philo_sleep(philo, philo->data->sleep_time);
		philo_status(philo, 't');
		usleep(100);
	}
}
