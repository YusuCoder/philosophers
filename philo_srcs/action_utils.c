/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:23:47 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/05 13:00:28 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_end(t_ryusupov *philo)
{
	pthread_mutex_lock(&philo->data->mutex_st);
	philo->data->end = 1;
	pthread_mutex_unlock(&philo->data->mutex_st);
	put_death(philo);
}

void	philo_take_forks_left_first(t_ryusupov *philo, t_fork_info *fork_info)
{
	pthread_mutex_lock(&philo->data->mutexx[fork_info->left_index]);
	*(fork_info->left_fork) = 0;
	pthread_mutex_unlock(&philo->data->mutexx[fork_info->left_index]);
	philo_status(philo, 'f');
	pthread_mutex_lock(&philo->data->mutexx[fork_info->right_index]);
	*(fork_info->right_fork) = 0;
	pthread_mutex_unlock(&philo->data->mutexx[fork_info->right_index]);
	philo_status(philo, 'f');
}

void	philo_take_forks_right_first(t_ryusupov *philo, t_fork_info *fork_info)
{
	pthread_mutex_lock(&philo->data->mutexx[fork_info->right_index]);
	*(fork_info->right_fork) = 0;
	pthread_mutex_unlock(&philo->data->mutexx[fork_info->right_index]);
	philo_status(philo, 'f');
	pthread_mutex_lock(&philo->data->mutexx[fork_info->left_index]);
	*(fork_info->left_fork) = 0;
	pthread_mutex_unlock(&philo->data->mutexx[fork_info->left_index]);
	philo_status(philo, 'f');
}

void	setup_fork_info(t_ryusupov *philo, t_fork_info *fork_info)
{
	fork_info->right_fork = &philo->data->forks[philo->i_philo];
	fork_info->left_fork = &philo->data->forks[get_index(philo, philo->i_philo
			- 1)];
	fork_info->left_index = get_index(philo, philo->i_philo - 1);
	fork_info->right_index = philo->i_philo;
}

int	lock_forks(t_ryusupov *philo, t_fork_info *fork_info)
{
	if (fork_info->left_index < fork_info->right_index)
	{
		pthread_mutex_lock(&philo->data->mutexx[fork_info->left_index]);
		pthread_mutex_lock(&philo->data->mutexx[fork_info->right_index]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->mutexx[fork_info->right_index]);
		pthread_mutex_lock(&philo->data->mutexx[fork_info->left_index]);
	}
	pthread_mutex_lock(&philo->data->mutex_st);
	philo->is_locked = 1;
	if (philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->mutex_st);
		pthread_mutex_unlock(&philo->data->mutexx[fork_info->left_index]);
		pthread_mutex_unlock(&philo->data->mutexx[fork_info->right_index]);
		return (1);
	}
	if (philo->is_locked)
	{
		pthread_mutex_unlock(&philo->data->mutex_st);
		philo->is_locked = 0;
	}
	return (0);
}
