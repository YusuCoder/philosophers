/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_th_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:51:01 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/23 15:25:34 by ryusupov         ###   ########.fr       */
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
		usleep(10);
	}
}

void	routine_loop(t_ryusupov *philo)
{
	while (1)
	{
		philo_death(philo);
		pthread_mutex_lock(&philo->data->mutex_death);
		if (philo->data->end == 1)
		{
			pthread_mutex_unlock(&philo->data->mutex_death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex_death);
		pthread_mutex_lock(&philo->data->mutex_death);
		if (philo->data->end == 0)
		{
			pthread_mutex_unlock(&philo->data->mutex_death);
			think_eat_sleep(philo, philo->i_philo);
			usleep(10);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->mutex_death);
			break ;
		}
	}
}
