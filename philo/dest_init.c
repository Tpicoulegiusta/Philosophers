/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dest_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:20:42 by tpicoule          #+#    #+#             */
/*   Updated: 2024/03/05 13:54:19 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->data.nb_ph - 1)
		pthread_mutex_destroy(&all->philos[i].l_fork);
	free(all->philos);
	pthread_mutex_destroy(&all->data.mutex);
	pthread_mutex_destroy(&all->data.tab_lmeal_mutex);
	pthread_mutex_destroy(&all->data.static_mutex);
	pthread_mutex_destroy(&all->data.mutex_print);
	pthread_mutex_destroy(&all->data.mutex_eat);
}
