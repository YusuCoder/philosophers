/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:30:10 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/14 15:12:11 by ryusupov         ###   ########.fr       */
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
/*---------Structs---------*/
typedef struct s_ryusupov
{
	int	i;
	int	*forks;
	int	eat_time;
	int	death;
	int	sleep_time;
	int	eat_count;

}	t_ryusupov;

/*--------------Finction definitions------------*/
int	valid_input(int argc, char** argv);
int	error_msg(char* msg, int return_value);

#endif
