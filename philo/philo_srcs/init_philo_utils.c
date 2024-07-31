/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:30:52 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/31 13:31:14 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philo(t_ryusupov *philo, t_ryusupov *data, int i)
{
	philo->i_philo = i;
	philo->t_food = data->begin;
	philo->food = 0;
	philo->data = data;
}

void	init_mutex(t_ryusupov *data)
{
	data->philos = malloc(sizeof(pthread_t) * data->philo_count);
	pthread_mutex_init(&data->mutex_st, NULL);
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->routine_mutex, NULL);
}

void	count_check(t_ryusupov *data, int i)
{
	if (i == data->philo_count - 1)
		data_time(data);
}
