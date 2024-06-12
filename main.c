/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:28:22 by ryusupov          #+#    #+#             */
/*   Updated: 2024/06/12 19:18:36 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char** argv)
{
	// t_ryusupov	data;
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		printf("Error!\nPlease check the arguments provided!\n");
	}
	else
	{
		printf("Success!");
	}
	return (0);
}
