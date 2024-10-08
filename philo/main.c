/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:28:22 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/24 17:42:37 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ryusupov	data;

	if (argc < 5 || argc > 6)
		return (error_msg("Error! Please check the args!\n", 0));
	if (!valid_input(argc, argv))
	{
		init_values(&data, argc, argv);
		if (data.eat_count < 1)
			return (0);
		init_threads(&data);
	}
	else
		return (error_msg("Error!\n", 0));
	return (0);
}
