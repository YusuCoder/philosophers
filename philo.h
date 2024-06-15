/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:30:10 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/15 18:44:02 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
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
	struct timeval		t_time;
	struct timeval		t_food;
	pthread_mutex_t		*mutexx;
	pthread_mutex_t		mutex_st;
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
int		ft_atoi(char *str);
int		is_digit(char *str);

#endif
