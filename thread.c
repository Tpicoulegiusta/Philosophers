/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommi <tommi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:44:14 by tpicoule          #+#    #+#             */
/*   Updated: 2024/02/23 17:01:10 by tommi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_all all, int id)
{
	if (id == all.data.nb_philo)
	{
		pthread_mutex_lock(&all.philos[id].left_fork);
		pthread_mutex_lock(&all.philos[0].left_fork);
	}
	else
	{
		pthread_mutex_lock(&all.philos[id].left_fork);
		pthread_mutex_lock(&all.philos[id + 1].left_fork);
	}
}

void	ft_drop_fork(t_all all, int id)
{
		if (id == all.data.nb_philo)
	{
		pthread_mutex_unlock(&all.philos[id].left_fork);
		pthread_mutex_unlock(&all.philos[0].left_fork);
	}
	else
	{
		pthread_mutex_unlock(&all.philos[id].left_fork);
		pthread_mutex_unlock(&all.philos[id + 1].left_fork);
	}
}

void	ft_eat(t_all all, int id)
{
	(void) id;
	(void) all;
	pthread_mutex_lock(&all.data.mutex_eat);
	ft_take_fork(all, id);
	printf("%ld Philo %d is eating\n", actual_time_ms() - all.data.start_time, id + 1);
	ft_usleep(all.data.teat);
	ft_drop_fork(all, id);
	pthread_mutex_unlock(&all.data.mutex_eat);
}

void lil_check(t_all all, int id)
{
	if (all.data.nb_philo != 1)
		{
			if(id % 2 == 0)
				ft_usleep(60);
		}
}

int	ft_check_death(t_all all)
{
	int i;

	i = 0;
	while(i < all.data.nb_philo)
	{
		if (actual_time_ms() - all.philos[i].tab_lmeal > all.data.tdie)
		{
			printf("result[%d]=%ld\n", i, actual_time_ms() - all.philos[i].tab_lmeal);
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
	lil_check(*all, id);
	while(all->is_sim != 0)
	{
		ft_eat(*all, id);
		printf("%ld Philo %d is eating\n", actual_time_ms() - all->data.start_time, id + 1);
		ft_usleep(all->data.teat);
		all->philos[id].tab_lmeal = actual_time_ms();
		printf("%ld Philo %d is sleeping\n", actual_time_ms() - all->data.start_time, id + 1);
		ft_usleep(all->data.tslp);
		printf("%ld Philo %d is thinking\n", actual_time_ms() - all->data.start_time, id + 1);
	}
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
		i++;
	}
	//puts("soleil");
}

