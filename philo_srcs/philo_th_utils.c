/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_th_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:51:01 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/08 15:30:01 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_fork_available(t_ryusupov *philo, t_fork_info fork_info)
{
	*(fork_info.left_fork) = 1;
	*(fork_info.right_fork) = 1;
	pthread_mutex_unlock(&philo->data->mutexx[fork_info.left_index]);
	pthread_mutex_unlock(&philo->data->mutexx[fork_info.right_index]);
}

void	wait_for_start(t_ryusupov *philo)
{
	int	tv_usec_value;

	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_st);
		tv_usec_value = philo->data->begin.tv_usec;
		if (tv_usec_value != 0)
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
		if (philo->data->end == 1)
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
			usleep(500);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->mutex_st);
			break ;
		}
	}
}
