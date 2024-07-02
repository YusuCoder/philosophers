/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:28:09 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/02 16:45:53 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_death(t_ryusupov *philo)
{
	pthread_mutex_lock(&philo->data->mutex_st);
	philo->is_locked = 1;
	if (philo->data->end == 0)
	{
		pthread_mutex_unlock(&philo->data->mutex_st);
		philo->is_locked = 0;
		if (calc_time(the_time(), philo->t_food) > philo->data->death_time)
		{
			put_death(philo);
			pthread_mutex_lock(&philo->data->mutex_st);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->mutex_st);
		}
		if (philo->data->completed_eating == philo->data->philo_count)
		{
			pthread_mutex_lock(&philo->data->mutex_st);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->mutex_st);
		}
	}
	if (philo->is_locked)
	{
		pthread_mutex_unlock(&philo->data->mutex_st);
		philo->is_locked = 0;
	}
}

void	philo_sleep(t_ryusupov *philo, int i)
{
	struct timeval	time;
	struct timeval	now;
	int				res;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&philo->data->mutex_st);
	res = calc_time(time, philo->data->begin);
	pthread_mutex_unlock(&philo->data->mutex_st);
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
	{
		philo_take_forks_right_first(philo, &fork_info);
	}
	gettimeofday(&philo->t_food, NULL);
	philo->food++;
	if (philo->food == philo->data->eat_count)
		philo->data->completed_eating++;
	philo_status(philo, 'e');
	philo_sleep(philo, philo->data->eat_time);
	*(fork_info.left_fork) = 1;
	pthread_mutex_lock(&philo->data->mutexx[fork_info.right_index]);
	*(fork_info.right_fork) = 1;
	pthread_mutex_unlock(&philo->data->mutexx[fork_info.right_index]);
}

void	think_eat_sleep(t_ryusupov *philo, int i)
{
	t_fork_info	fork_info;

	setup_fork_info(philo, &fork_info);
	if (philo->data->end)
		return ;
	if (lock_forks(philo, &fork_info))
		return ;
	if (*fork_info.left_fork == 1 && *fork_info.right_fork == 1)
	{
		*fork_info.left_fork = 0;
		*fork_info.right_fork = 0;
		pthread_mutex_unlock(&philo->data->mutexx[fork_info.left_index]);
		pthread_mutex_unlock(&philo->data->mutexx[fork_info.right_index]);
		philo_eat(philo, fork_info.right_fork, fork_info.left_fork, i);
		philo_status(philo, 's');
		philo_sleep(philo, philo->data->sleep_time);
		philo_status(philo, 't');
		usleep(200);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->mutexx[fork_info.left_index]);
		pthread_mutex_unlock(&philo->data->mutexx[fork_info.right_index]);
	}
}
