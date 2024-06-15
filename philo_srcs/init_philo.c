/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:34:36 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/15 18:46:57 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_mutex_t	*ft_mutexx(int philo_c)
{
	pthread_mutex_t	*res;

	res = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (philo_c + 1));
	if (!res)
		return (0);
	return (res);
}

int	*put_forks(int philo_c)
{
	int	*res;
	int	i;

	i = 0;
	res = (int *)malloc(sizeof(int) * (philo_c + 1));
	if (!res)
		return (0);
	while (i < philo_c)
	{
		res[i] = 1;
		i++;
	}
	res[i] = -1;
	return (res);
}

void	init_values(t_ryusupov *data, int argc, char **argv)
{
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	else
		data->eat_count = -1;
	data->philo_count = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->forks = put_forks(data->philo_count);
	data->mutexx = ft_mutexx(data->philo_count);
	data->completed_eating = 0;
	data->end = 0;
	data->t_time.tv_sec = 0;
	data->t_time.tv_usec = 0;
}

void	init_threads(t_ryusupov *data)
{
	pthread_t	*philo;
	int			i;
	t_ryusupov	*philo_data;

	philo = malloc(sizeof(pthread_t) * data->philo_count);
	i = 0;
	pthread_mutex_init(&data->mutex_st, NULL);
	pthread_mutex_init(&data->mutex_death, NULL);
	while (i < data->philo_count)
	{
		if (i == data->philo_count - 1)
			gettimeofday(&data->t_time, NULL);
		philo_data = malloc(sizeof(t_ryusupov));
		init_philo(philo_data, data, i);
		pthread_mutex_init(&data->mutexx[i], NULL);
		if (pthread_create(&philo[i], NULL, routine, philo_data) != 0)
		{
			printf("Failed to create thread %d\n", i);
			break ;
		}
		i++;
	}
	join_threads(data, philo);
	free(philo);
}
