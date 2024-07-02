/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:23:47 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/02 12:16:17 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

