/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:28:09 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/11 15:31:50 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	while (1)
	{
		gettimeofday(&now, NULL);
		if (calc_time(now, philo->data->begin) >= res)
			break ;
		philo_death(philo);
		usleep(300);
	}
}

void	philo_take_forks(t_philo_args *args, t_fork_info *fork_info)
{
	fork_info->left_index = get_index(args->philo, args->i - 1);
	fork_info->right_index = args->i;
	fork_info->left_fork = args->left_fork;
	fork_info->right_fork = args->right_fork;
	if (fork_info->left_index < fork_info->right_index)
		philo_take_forks_left_first(args->philo, fork_info);
	else
		philo_take_forks_right_first(args->philo, fork_info);
}

void	philo_eat_and_release(t_ryusupov *philo, t_fork_info *fork_info)
{
	gettimeofday(&philo->t_food, NULL);
	philo->food++;
	pthread_mutex_lock(&philo->data->mutex_st);
	if (philo->food == philo->data->eat_count)
	{
		philo->data->completed_eating++;
		if (philo->data->completed_eating == philo->data->philo_count)
			philo->data->end = 1;
		pthread_mutex_unlock(&philo->data->mutex_st);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_st);
	philo_status(philo, 'e');
	philo_sleep(philo, philo->data->eat_time);
	if (lock_forks(philo, fork_info))
		return ;
	set_fork_available(philo, *fork_info);
}

void	philo_eat(t_ryusupov *philo, int *right_fork, int *left_fork, int i)
{
	t_philo_args	args;
	t_fork_info		fork_info;

	args.philo = philo;
	args.right_fork = right_fork;
	args.left_fork = left_fork;
	args.i = i;
	philo_take_forks(&args, &fork_info);
	philo_eat_and_release(philo, &fork_info);
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
		usleep(1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->mutexx[fork_info.left_index]);
		pthread_mutex_unlock(&philo->data->mutexx[fork_info.right_index]);
	}
}
