/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:28:09 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/31 19:07:31 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_sleep(t_ryusupov *philo, int i)
{
	struct timeval	time;
	struct timeval	now;
	int				res;

	pthread_mutex_lock(&philo->data->mutex_st);
	gettimeofday(&time, NULL);
	res = calc_time(time, philo->data->begin);
	pthread_mutex_unlock(&philo->data->mutex_st);
	res += i;
	while (1)
	{
		gettimeofday(&now, NULL);
		if (calc_time(now, philo->data->begin) >= res)
			break ;
		philo_death(philo);
		usleep(10);
	}
}

int	prepare_to_eat(t_ryusupov *philo, t_fork_info *fork_info)
{
	setup_fork_info(philo, fork_info);
	pthread_mutex_lock(&philo->data->mutex_death);
	if (philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->mutex_death);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex_death);
	if (lock_forks(philo, fork_info))
		return (0);
	return (1);
}

void	perform_actions(t_ryusupov *philo, t_fork_info *fork_info, int i)
{
	if (*fork_info->left_fork == 1 && *fork_info->right_fork == 1)
	{
		*fork_info->left_fork = 0;
		*fork_info->right_fork = 0;
		pthread_mutex_unlock(&philo->data->mutexx[fork_info->left_index]);
		pthread_mutex_unlock(&philo->data->mutexx[fork_info->right_index]);
		philo_eat(philo, fork_info->right_fork, fork_info->left_fork, i);
		philo_status(philo, 's');
		philo_sleep(philo, philo->data->sleep_time);
		philo_status(philo, 't');
		usleep(1000);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->mutexx[fork_info->left_index]);
		pthread_mutex_unlock(&philo->data->mutexx[fork_info->right_index]);
	}
}

void	think_eat_sleep(t_ryusupov *philo, int i)
{
	t_fork_info	fork_info;

	if (prepare_to_eat(philo, &fork_info))
	{
		perform_actions(philo, &fork_info, i);
	}
}
