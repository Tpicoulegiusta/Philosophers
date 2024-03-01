/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:43:44 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/01 16:59:26 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_all	all;

	if (check_args(argc, argv) != 0)
		return (write(1, "bad args\n", 9), 1);
	if (check_args_2(argv, &all) != 0)
		return (write(1, "bad argsss\n", 9), 1);
	all.philos = malloc(sizeof(t_ph) * all.data.nb_philo);
	if (!all.philos)
		return (write(1, "malloc\n", 7), 1);
	ft_init(&all);
	while (1)
	{
		if (ft_check_death(&all) != 0)
			break ;
	}
	while(ft_check_thread(&all))
		ft_usleep(10);
	//ft_usleep(100);
	destroy_all(&all);
	return (0);
}

void	ft_init(t_all *all)
{
	pthread_mutex_init(&all->data.mutex, NULL);
	pthread_mutex_init(&all->data.mutex_print, NULL);
	pthread_mutex_init(&all->data.tab_lmeal_mutex, NULL);
	pthread_mutex_init(&all->data.static_mutex, NULL);
	pthread_mutex_init(&all->data.mutex_eat, NULL);
	all->is_sim = 1;
	ft_thread_philo(all);
}

int	ft_check_death(t_all *all)
{
	int		i;
	int		nb_eat;
	long	diff;

	i = 0;
	nb_eat = 0;
	while (i < all->data.nb_philo)
	{
		pthread_mutex_lock(&all->data.tab_lmeal_mutex);
		diff = actual_time_ms() - all->philos[i].tab_lmeal;
		pthread_mutex_unlock(&all->data.tab_lmeal_mutex);
		if (diff > all->data.tdie)
		{
			pthread_mutex_lock(&all->data.mutex_print);
			all->is_sim = 0;
			pthread_mutex_unlock(&all->data.mutex_print);
			printf("ivan %d died at %ld\n", (i + 1), diff);
			return (write(1, "death\n", 6), 1);
		}
		if (all->philos[i].count_eat == all->data.meat)
			nb_eat++;
		i++;
	}
	if (nb_eat >= all->data.nb_philo)
	{
		pthread_mutex_lock(&all->data.mutex_print);
		all->is_sim = 0;
		pthread_mutex_unlock(&all->data.mutex_print);
		printf("Ils ont manged/n\n");
		return (1);
	}
	return (0);
}

int	ft_check_thread(t_all *all)
{
	int	i;
	int thread;

	i = 0;
	thread = 0;
	while (1)
	{
		pthread_mutex_lock(&all->data.mutex);
		if (i == all->data.nb_philo || !(&all->philos[i]))
		{
			pthread_mutex_unlock(&all->data.mutex);
			printf("thread == %d\n", thread);
			return (thread);
		}
		if(all->philos[i].philo_thread)
		{
			puts("caca");
			thread++;
		}
		i++;
		pthread_mutex_unlock(&all->data.mutex);
	}
	return (thread);
}
