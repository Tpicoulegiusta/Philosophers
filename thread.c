/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:44:14 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/01 14:41:50 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thread_philo(t_all *all)
{
	int	i;

	all->data.start_time = actual_time_ms();
	i = -1;
	while (++i < all->data.nb_philo && all->data.nb_philo != 0)
		pthread_mutex_init(&all->philos[i].left_fork, NULL);
	i = 0;
	while (i < all->data.nb_philo && all->data.nb_philo != 0)
	{
		all->philos[i].count_eat = 0;
		all->philos[i].tab_lmeal = all->data.start_time;
		pthread_create(&all->philos[i].philo_thread, NULL,
			(void *) &routine, all);
		i++;
	}
}

void	routine(t_all *all)
{
	static int	static_id;
	int			id;

	pthread_mutex_lock(&all->data.static_mutex);
	id = static_id;
	static_id++;
	pthread_mutex_unlock(&all->data.static_mutex);
	lil_check(*all, id);
	while (1)
	{
		pthread_mutex_lock(&all->data.mutex_print);
		if (all->is_sim == 0)
			break ;
		pthread_mutex_unlock(&all->data.mutex_print);
		ft_eat(all, id);
		ft_print(all, id, "is sleeping");
		ft_usleep(all->data.tslp);
		ft_print(all, id, "is thinking");
	}
	pthread_mutex_unlock(&all->data.mutex_print);
	pthread_detach(all->philos[id].philo_thread);
	printf("%d je suis mort lol\n", id);
}

void	ft_eat(t_all *all, int id)
{

	ft_take_fork(all, id);
	ft_print(all, id, "is eating");
	pthread_mutex_lock(&all->data.tab_lmeal_mutex);
	all->philos[id].tab_lmeal = actual_time_ms();
	pthread_mutex_unlock(&all->data.tab_lmeal_mutex);
	ft_usleep(all->data.teat);
	ft_drop_fork(all, id);
	if (all->philos[id].count_eat < all->data.meat)
		all->philos[id].count_eat += 1;
}

void	ft_print(t_all *all, int id, char *str)
{
	pthread_mutex_lock(&all->data.mutex_print);
	if (all->is_sim == 1)
		printf("%ld Philo %d %s\n", actual_time_ms() - all->data.start_time,
			(id + 1), str);
	pthread_mutex_unlock(&all->data.mutex_print);
}

void	lil_check(t_all all, int id)
{
	if (all.data.nb_philo != 1)
	{
		if (id % 2)
			ft_usleep(60);
	}
}
