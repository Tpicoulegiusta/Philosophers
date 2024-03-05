/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:44:14 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/05 15:04:11 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thread_philo(t_all *all)
{
	int	i;

	all->data.start_t = actual_time_ms();
	i = -1;
	while (++i < all->data.nb_ph && all->data.nb_ph != 0)
		pthread_mutex_init(&all->philos[i].l_fork, NULL);
	i = 0;
	while (i < all->data.nb_ph && all->data.nb_ph != 0)
	{
		all->philos[i].count_eat = 0;
		all->philos[i].tab_lmeal = all->data.start_t;
		pthread_create(&all->philos[i].philo_thread, NULL,
			(void *) &routine, all);
		i++;
	}
}

void	ft_routine_2(t_all *all, int id)
{
	ft_eat(all, id);
	ft_print(all, id, "is sleeping");
	ft_usleep(all->data.tslp);
	ft_print(all, id, "is thinking");
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
	if (all->data.nb_ph == 1)
	{
		ft_usleep(all->data.tdie);
		return ;
	}
	while (1)
	{
		pthread_mutex_lock(&all->data.mutex_print);
		if (all->is_sim == 0)
			break ;
		pthread_mutex_unlock(&all->data.mutex_print);
		ft_routine_2(all, id);
	}
	pthread_mutex_unlock(&all->data.mutex_print);
	return ;
}

void	ft_print(t_all *all, int id, char *str)
{
	pthread_mutex_lock(&all->data.mutex_print);
	if (all->is_sim == 1)
		printf("%ld Philo %d %s\n", actual_time_ms() - all->data.start_t,
			(id + 1), str);
	pthread_mutex_unlock(&all->data.mutex_print);
}

void	lil_check(t_all all, int id)
{
	if (all.data.nb_ph != 1)
	{
		if (id % 2)
			ft_usleep(60);
	}
}
