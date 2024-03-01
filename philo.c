/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:43:44 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/01 11:19:36 by tpicoule         ###   ########.fr       */
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
		ft_usleep(1);
	}
	//printf("%d\n", all.is_sim);
	return (0);
}

void	ft_init(t_all *all)
{
	pthread_mutex_init(&all->data.mutex, NULL);
	pthread_mutex_init(&all->data.mutex_print, NULL);
	pthread_mutex_init(&all->data.mutex_eat, NULL);
	pthread_mutex_lock(&all->data.mutex_print);
	all->is_sim = 1;
	pthread_mutex_unlock(&all->data.mutex_print);
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
		diff = actual_time_ms() - all->philos[i].tab_lmeal;
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
