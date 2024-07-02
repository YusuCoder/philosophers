/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:25:25 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/02 17:17:51 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

struct timeval	the_time(void)
{
	struct timeval	t_now;

	gettimeofday(&t_now, NULL);
	return (t_now);
}

int	calc_time(struct timeval now, struct timeval start)
{
	int	result;

	result = (now.tv_sec * 1000 + now.tv_usec / 1000);
	result -= (start.tv_sec * 1000 + start.tv_usec / 1000);
	return (result);
}

int	calculate_time(struct timeval now, struct timeval begin)
{
	int	res;

	res = (now.tv_sec * 1000 + now.tv_usec / 1000);
	res = (begin.tv_sec * 1000 + begin.tv_sec / 1000);
	return (res);
}

int	get_index(t_ryusupov *philo, int i)
{
	if (i < 0)
		return (philo->data->philo_count - 1);
	return (i);
}

void	data_time(t_ryusupov *data)
{
	pthread_mutex_lock(&data->mutex_st);
	gettimeofday(&data->begin, NULL);
	pthread_mutex_unlock(&data->mutex_st);
}
