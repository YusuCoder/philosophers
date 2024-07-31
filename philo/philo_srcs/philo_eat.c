/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:54:14 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/31 19:20:05 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_take_forks(t_philo_args *args, t_fork_info *fork_info)
{
	fork_info->left_index = get_index(args->philo, args->i - 1);
	fork_info->right_index = args->i;
	fork_info->left_fork = args->left_fork;
	fork_info->right_fork = args->right_fork;
	if (fork_info->left_index < fork_info->right_index)
		take_forks(args->philo, fork_info);
	else
		take_forks(args->philo, fork_info);
}

void	philo_eat_and_release(t_ryusupov *philo, t_fork_info *fork_info)
{
	gettimeofday(&philo->t_food, NULL);
	philo->food++;
	pthread_mutex_lock(&philo->data->mutex_st);
	if (philo->food > philo->data->eat_count)
	{
		pthread_mutex_unlock(&philo->data->mutex_st);
		pthread_mutex_lock(&philo->data->routine_mutex);
		philo->data->completed_eating++;
		pthread_mutex_unlock(&philo->data->routine_mutex);
		if (philo->data->completed_eating == philo->data->philo_count)
		{
			pthread_mutex_lock(&philo->data->mutex_death);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->mutex_death);
		}
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
