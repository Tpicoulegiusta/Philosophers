/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:44:14 by tpicoule          #+#    #+#             */
/*   Updated: 2024/02/20 15:46:23 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death(t_all all)
{
	int i;

	i = 0;
	while(i < all.data.nb_philo)
	{
		if (actual_time_ms() - all.philos[i].tab_lmeal > all.data.tdie)
		{
			printf("resulty[%d]=%ld\n", i, actual_time_ms() - all.philos[i].tab_lmeal);
			all.is_sim = 0;
			return(write(1, "death\n", 6), 1);
		}
		i++;
	}
	return(0);
}

void routine(t_all *all)
{
	static int	static_id;
	int			id;

	id = static_id;
	static_id++;
	while(all->is_sim != 0)
	{
		//printf("%d je mange\n", id);
		//timestamp_in_ms X is eating
		printf("%ld Philo %d is eating\n", actual_time_ms() - all->data.start_time, id + 1);
		usleep(all->data.teat * 1000);
		all->philos[id].tab_lmeal = actual_time_ms();
	}
	//g fini

	// je mange
	// last_meal = gettimeofmyday()
	// je dodo
	// je pense
}

void ft_thread_philo(t_all *all)
{

    int i;

    i = 0;
	all->data.start_time = actual_time_ms();
	while (i < all->data.nb_philo)
	{
		all->philos[i].tab_lmeal = all->data.start_time;
		pthread_mutex_init(&all->philos[i].left_fork, NULL);
		pthread_create(&all->philos[i].philo_thread, NULL, (void*) &routine, all);
		//printf("philo -> %d\n", i);
		i++;
	}
 	/*
		while(1)
			// attendre(1 usec)
			// si mort
			// breack;
	*/
	//usleep(500);
	// if(lwe phoilo na pas mang2 depuis tdie)
	//     la fin des arikos
	//puts("soleil");
}

