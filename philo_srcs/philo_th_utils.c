/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:51:01 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/26 17:51:39 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_for_start(t_ryusupov *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_st);
		if (philo->data->begin.tv_usec != 0)
		{
			pthread_mutex_unlock(&philo->data->mutex_st);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex_st);
		usleep(100);
	}
}

void	routine_loop(t_ryusupov *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_st);
		if (philo->data->end != 0)
		{
			pthread_mutex_unlock(&philo->data->mutex_st);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex_st);
		philo_death(philo);
		pthread_mutex_lock(&philo->data->mutex_st);
		if (philo->data->end == 0)
		{
			pthread_mutex_unlock(&philo->data->mutex_st);
			think_eat_sleep(philo, philo->i_philo);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->mutex_st);
			break ;
		}
	}
}
