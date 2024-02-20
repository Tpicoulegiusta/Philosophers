/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:44:14 by tpicoule          #+#    #+#             */
/*   Updated: 2024/02/19 17:41:53 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void routine(t_all *all)
{
	pthread_mutex_lock(&all->data.mutex);
	printf("Hello je suis le philo %d\n", all->philos->id + 1);
	pthread_mutex_unlock(&all->data.mutex);
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
		all->philos->id = i;
		//all->data.last_meal[i] = all->data.start_time
		pthread_mutex_init(&all->philos[i].left_fork, NULL);
		pthread_create(&all->philos[i].philo_thread, NULL, (void*) &routine, all);
		printf("philo -> %d\n", all->philos->id);
		i++;
	}
 	/*
		while(1)
			// attendre(1 usec)
			// si mort
			// breack;
	*/
	//usleep(5000);
	// if(lwe phoilo na pas mang2 depuis tdie)
	//     la fin des arikos
	puts("soleil");
}

