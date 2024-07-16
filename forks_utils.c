/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:21:04 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/01 11:22:08 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_all *all, int id)
{
	if ((all->data.nb_philo % 2 && id > 0) || (all->data.nb_philo > 0 && id % 2))
	{
		pthread_mutex_lock(&all->philos[id].left_fork);
		ft_print(all, id, "has taken a fork");
		pthread_mutex_lock(&all->philos[(id + 1) % all->data.nb_philo].left_fork);
		ft_print(all, id, "has taken a fork");
		return ;
	}
		pthread_mutex_lock(&all->philos[(id + 1) % all->data.nb_philo].left_fork);
		ft_print(all, id, "has taken a fork");
		pthread_mutex_lock(&all->philos[id].left_fork);
		ft_print(all, id, "has taken a fork");
}

void	ft_drop_fork(t_all *all, int id)
{
	if ((all->data.nb_philo % 2 && id > 0) || (all->data.nb_philo > 0 && id % 2))
	{
		pthread_mutex_unlock(&all->philos[id].left_fork);
		pthread_mutex_unlock(&all->philos[(id + 1) % all->data.nb_philo].left_fork);
		return ;
	}
		pthread_mutex_unlock(&all->philos[id].left_fork);
		pthread_mutex_unlock(&all->philos[(id + 1)].left_fork);
}
