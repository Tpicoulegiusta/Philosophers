/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:21:04 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/05 14:50:34 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_try(t_all *all, int id)
{
	ft_print(all, id, "is eating");
	pthread_mutex_lock(&all->data.tab_lmeal_mutex);
	all->philos[id].tab_lmeal = actual_time_ms();
	pthread_mutex_unlock(&all->data.tab_lmeal_mutex);
	ft_usleep(all->data.teat);
	pthread_mutex_lock(&all->data.mutex_count_eat);
	if (all->philos[id].count_eat < all->data.meat)
		all->philos[id].count_eat += 1;
	pthread_mutex_unlock(&all->data.mutex_count_eat);
}

void	ft_eat(t_all *all, int id)
{
	if ((all->data.nb_ph % 2 && id > 0) || (all->data.nb_ph > 0 && id % 2))
	{
		pthread_mutex_lock(&all->philos[id].l_fork);
		ft_print(all, id, "has taken a fork");
		pthread_mutex_lock(&all->philos[(id + 1) % all->data.nb_ph].l_fork);
		ft_print(all, id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&all->philos[(id + 1) % all->data.nb_ph].l_fork);
		ft_print(all, id, "has taken a fork");
		pthread_mutex_lock(&all->philos[id].l_fork);
		ft_print(all, id, "has taken a fork");
	}
	ft_try(all, id);
	if ((all->data.nb_ph % 2 && id > 0) || (all->data.nb_ph > 0 && id % 2))
	{
		pthread_mutex_unlock(&all->philos[id].l_fork);
		pthread_mutex_unlock(&all->philos[(id + 1) % all->data.nb_ph].l_fork);
	}
	else
	{
		pthread_mutex_unlock(&all->philos[(id + 1) % all->data.nb_ph].l_fork);
		pthread_mutex_unlock(&all->philos[id].l_fork);
	}
}
