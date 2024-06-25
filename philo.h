/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:30:10 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/25 14:10:53 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define CYAN "\x1b[35m"
# define RESET "\x1b[0m"
//ANSI TEXT STYLE
# define BOLD "\x1b[1m"
# define RESET "\x1b[0m"
/*-------Standart libraries-------*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>
/*---------Structs---------*/
typedef struct s_ryusupov
{
	int					i;
	int					*forks;
	int					eat_time;
	int					death_time;
	int					sleep_time;
	int					eat_count;
	int					philo_count;
	int					completed_eating;
	int					end;
	struct timeval		t_food;
	struct timeval		now;
	struct timeval		begin;
	pthread_mutex_t		*mutexx;
	pthread_mutex_t		mutex_st;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		mutex_death;
	int					i_philo;
	int					food;
	struct s_ryusupov	*data;
}						t_ryusupov;

/*--------------Finction definitions------------*/
int		valid_input(int argc, char** argv);
void	init_values(t_ryusupov *data, int argc, char **argv);
/*-------------Helper functions-------------*/
int		error_msg(char* msg, int return_value);
int		ft_atoi(const char *str);
int		is_digit(char *str);
int		get_index(t_ryusupov *philo, int i);
/*--------------Actions----------------*/
void	*routine(void *argv);
void	philo_death(t_ryusupov *philo);
void	think_eat_sleep(t_ryusupov *philo, int i);
void	philo_status(t_ryusupov *philo, char c);
int		calc_time(struct timeval now, struct timeval start);
void	philo_sleep(t_ryusupov *philo, int i);
void	init_threads(t_ryusupov *data);
void	join_threads (t_ryusupov *data, pthread_t *philo);
void	put_death(t_ryusupov *philo);
int		calc_timestamp(struct timeval start);

void	ft_free_c_data(t_ryusupov *c_data);

#endif
