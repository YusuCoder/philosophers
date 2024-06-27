/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:23:47 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/27 18:56:46 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_take_forks_left_first(t_ryusupov *philo, t_fork_info *fork_info)
{
	pthread_mutex_lock(&philo->data->fork_mutex);
	*(fork_info->left_fork) = 0;
	philo_status(philo, 'f');
	pthread_mutex_unlock(&philo->data->fork_mutex);
	pthread_mutex_lock(&philo->data->fork_mutex);
	*(fork_info->right_fork) = 0;
	philo_status(philo, 'f');
	pthread_mutex_unlock(&philo->data->fork_mutex);
}

void	philo_take_forks_right_first(t_ryusupov *philo, t_fork_info *fork_info)
{
	pthread_mutex_lock(&philo->data->fork_mutex);
	*(fork_info->right_fork) = 0;
	philo_status(philo, 'f');
	pthread_mutex_unlock(&philo->data->fork_mutex);
	pthread_mutex_lock(&philo->data->fork_mutex);
	*(fork_info->left_fork) = 0;
	philo_status(philo, 'f');
	pthread_mutex_unlock(&philo->data->fork_mutex);
}
