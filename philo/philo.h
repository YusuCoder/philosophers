/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:30:10 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/31 13:53:50 by ryusupov         ###   ########.fr       */
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
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
/*---------Structs---------*/
typedef struct s_ryusupov	t_ryusupov;
typedef struct s_philo_args
{
	t_ryusupov			*philo;
	int					died;
	int					*right_fork;
	int					*left_fork;
	int					i;
}						t_philo_args;
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
	t_philo_args		*philo;
	pthread_t			*philos;
	pthread_t			m_thread;
	struct timeval		t_food;
	struct timeval		now;
	struct timeval		begin;
	pthread_mutex_t		*mutexx;
	pthread_mutex_t		mutex_st;
	pthread_mutex_t		routine_mutex;
	pthread_mutex_t		mutex_death;
	int					i_philo;
	int					food;
	int					is_locked;
	int					is_locked2;
	int					fork_flag;
	int					died;
	struct s_ryusupov	*data;
}						t_ryusupov;

typedef struct s_fork_info
{
	t_ryusupov			*philo;
	int					left_index;
	int					right_index;
	int					*left_fork;
	int					*right_fork;
	int					i;
}						t_fork_info;

/*--------------Finction definitions------------*/
int						valid_input(int argc, char **argv);
void					init_values(t_ryusupov *data, int argc, char **argv);
/*-------------Helper functions-------------*/
int						error_msg(char *msg, int return_value);
int						ft_atoi(const char *str);
int						is_digit(char *str);
int						get_index(t_ryusupov *philo, int i);
struct timeval			the_time(void);
/*--------------Actions----------------*/
void					*routine(void *argv);
void					*philo_death(void *data);
void					think_eat_sleep(t_ryusupov *philo, int i);
void					philo_status(t_ryusupov *philo, char c);
int						calc_time(struct timeval now, struct timeval start);
void					philo_sleep(t_ryusupov *philo, int i);
void					init_threads(t_ryusupov *data);
void					join_threads(t_ryusupov *data, pthread_t *philo);
void					put_death(t_ryusupov *philo);
int						calc_timestamp(struct timeval start);
void					take_forks(t_ryusupov *philo,
							t_fork_info *fork_info);
void					ft_free_c_data(t_ryusupov *c_data);
void					wait_for_start(t_ryusupov *philo);
void					routine_loop(t_ryusupov *philo);
void					setup_fork_info(t_ryusupov *philo,
							t_fork_info *fork_info);
int						lock_forks(t_ryusupov *philo, t_fork_info *fork_info);
void					data_time(t_ryusupov *data);
void					set_end(t_ryusupov *philo);
void					set_fork_available(t_ryusupov *philo,
							t_fork_info fork_info);
void					perform_actions(t_ryusupov *philo,
							t_fork_info *fork_info, int i);
int						prepare_to_eat(t_ryusupov *philo,
							t_fork_info *fork_info);
void					philo_eat(t_ryusupov *philo, int *right_fork,
							int *left_fork, int i);
void					init_philo(t_ryusupov *philo, t_ryusupov *data, int i);
void					init_mutex(t_ryusupov *data);
void					count_check(t_ryusupov *data, int i);
pthread_mutex_t			*ft_mutexx(int philo_c);

#endif
