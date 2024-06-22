/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:25:25 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/22 00:06:39 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
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

int	error_msg(char *msg, int return_value)
{
	printf("%s", msg);
	return (return_value);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	result;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (i < ft_strlen(str) || result > INT_MAX)
		return (0);
	return ((int)result);
}

// int	ft_atoi(char *str)
// {
// 	unsigned long long int	num;
// 	int						i;

// 	i = 0;
// 	num = 0;
// 	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
// 	{
// 		num = num * 10 + (str[i] - '0');
// 		i++;
// 	}
// 	if (num > INT_MAX)
// 		return (-1);
// 	return ((int)num);
// }

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
