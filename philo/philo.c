/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:43:44 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/05 14:55:09 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_all	all;

	if (check_args(argc, argv) != 0)
		return (write(1, "bad args\n", 9), 1);
	if (check_args_2(argv, &all) != 0)
		return (write(1, "bad args\n", 9), 1);
	all.philos = malloc(sizeof(t_ph) * all.data.nb_ph);
	if (!all.philos)
		return (write(1, "malloc\n", 7), 1);
	ft_init(&all);
	while (1)
	{
		if (ft_check_death(&all) != 0)
			break ;
	}
	ft_check_thread(&all);
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
	pthread_mutex_init(&all->data.mutex_count_eat, NULL);
	all->is_sim = 1;
	ft_thread_philo(all);
}

int	ft_eaten(t_all *all, int nb_eat)
{
	if (nb_eat >= all->data.nb_ph)
	{
		pthread_mutex_lock(&all->data.mutex_print);
		all->is_sim = 0;
		pthread_mutex_unlock(&all->data.mutex_print);
		printf("All philo ate \n");
		return (1);
	}
	return (0);
}

int	ft_check_death(t_all *all)
{
	int		i;
	int		nb_eat;
	long	diff;

	i = -1;
	nb_eat = 0;
	while (++i < all->data.nb_ph)
	{
		pthread_mutex_lock(&all->data.tab_lmeal_mutex);
		diff = actual_time_ms() - all->philos[i].tab_lmeal;
		pthread_mutex_unlock(&all->data.tab_lmeal_mutex);
		if (diff > all->data.tdie)
		{
			ft_print(all, i, "died");
			pthread_mutex_lock(&all->data.mutex_print);
			all->is_sim = 0;
			pthread_mutex_unlock(&all->data.mutex_print);
			return (1);
		}
		pthread_mutex_lock(&all->data.mutex_count_eat);
		if (all->philos[i].count_eat == all->data.meat)
			nb_eat++;
		pthread_mutex_unlock(&all->data.mutex_count_eat);
	}
	return (ft_eaten(all, nb_eat));
}

void	ft_check_thread(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data.nb_ph)
	{
		pthread_join(all->philos[i].philo_thread, NULL);
		i++;
	}
	return ;
}
