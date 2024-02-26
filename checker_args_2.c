/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_args_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommi <tommi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:35:26 by tpicoule          #+#    #+#             */
/*   Updated: 2024/02/22 11:42:42 by tommi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args_2(char **argv, t_all *all)
{
		all->data.nb_philo = ft_atoi(argv[1]);
		all->data.tdie = ft_atoi(argv[2]);
		all->data.teat = ft_atoi(argv[3]);
		all->data.tslp = ft_atoi(argv[4]);
		if (argv[5])
			all->data.meat = ft_atoi(argv[5]);
		if (all->data.nb_philo <= 0 || all->data.tdie <= 0 
		|| all->data.teat <= 0 || all->data.tslp <= 0 )
			return(1);
		return(0);
}

long int	actual_time_ms(void)
{
	struct timeval	timeval;
	long int	time_ms;

	gettimeofday(&timeval, NULL);
	time_ms = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
	return (time_ms);
}

void ft_usleep(int time)
{
	long int	start;

	start = actual_time_ms() + time;
	while(start > actual_time_ms())
		usleep(1);
}