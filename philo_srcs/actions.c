/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:28:09 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/25 14:20:50 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

struct timeval	the_time(void)
{
	struct timeval	t_now;

	gettimeofday(&t_now, NULL);
	return (t_now);
}

int	calc_time(struct timeval now, struct timeval start)
{
	int	result;

	result = (now.tv_sec * 1000 + now.tv_usec / 1000);
	result -= (start.tv_sec * 1000 + start.tv_usec / 1000);
	return (result);
}

void	philo_death(t_ryusupov *philo)
{
	pthread_mutex_lock(&philo->data->mutex_death);
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
	int	left_index;
	int	right_index;

	left_index = get_index(philo, i - 1);
	right_index = i;
	if (left_index < right_index)
	{
		pthread_mutex_lock(&philo->data->mutexx[left_index]);
		*left_fork = 0;
		philo_status(philo, 'f');
		pthread_mutex_lock(&philo->data->mutexx[right_index]);
		*right_fork = 0;
		philo_status(philo, 'f');
	}
	else
	{
		pthread_mutex_lock(&philo->data->mutexx[right_index]);
		*right_fork = 0;
		philo_status(philo, 'f');
		pthread_mutex_lock(&philo->data->mutexx[left_index]);
		*left_fork = 0;
		philo_status(philo, 'f');
	}
	gettimeofday(&philo->t_food, NULL);
	philo->food++;
	if (philo->food == philo->data->eat_count)
	{
		philo->data->completed_eating++;
	}
	philo_status(philo, 'e');
	philo_sleep(philo, philo->data->eat_time);
	*left_fork = 1;
	pthread_mutex_unlock(&philo->data->mutexx[left_index]);
	*right_fork = 1;
	pthread_mutex_unlock(&philo->data->mutexx[right_index]);
}

// void	philo_eat(t_ryusupov *philo, int *right_fork, int *left_fork, int i)
// {
// 	pthread_mutex_lock(&philo->data->mutexx[get_index(philo, i - 1)]);
// 	*left_fork = 0;
// 	philo_status(philo, 'f');
// 	pthread_mutex_lock(&philo->data->mutexx[i]);
// 	*right_fork = 0;
// 	philo_status(philo, 'f');
// 	gettimeofday(&philo->t_food, NULL);
// 	philo->food++;
// 	if (philo->food == philo->data->eat_count)
// 	{
// 		philo->data->completed_eating++;
// 		philo->food++;
// 	}
// 	philo_status(philo, 'e');
// 	philo_sleep(philo, philo->data->eat_time);
// 	*left_fork = 1;
// 	pthread_mutex_unlock(&philo->data->mutexx[get_index(philo, i - 1)]);
// 	*right_fork = 1;
// 	pthread_mutex_unlock(&philo->data->mutexx[i]);
// }


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
	}
}
